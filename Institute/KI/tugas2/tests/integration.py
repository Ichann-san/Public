import argparse
import socket
import struct
import subprocess
import threading
import time
from pathlib import Path


class Process:
    def __init__(self, binary, arguments):
        self.process = subprocess.Popen(
            [str(binary), *arguments], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT, text=True, encoding="utf-8", bufsize=1,
        )
        self.lines = []
        self.changed = threading.Condition()
        self.reader = threading.Thread(target=self._read, daemon=True)
        self.reader.start()

    def _read(self):
        for line in self.process.stdout:
            with self.changed:
                self.lines.append(line.rstrip("\n"))
                self.changed.notify_all()

    def mark(self):
        with self.changed:
            return len(self.lines)

    def send(self, text):
        self.process.stdin.write(text + "\n")
        self.process.stdin.flush()

    def wait(self, text, start=0, timeout=10):
        deadline = time.monotonic() + timeout
        with self.changed:
            while not any(text in line for line in self.lines[start:]):
                remaining = deadline - time.monotonic()
                if remaining <= 0 or self.process.poll() is not None:
                    raise AssertionError(f"Missing {text!r}; output: {self.lines[start:]}")
                self.changed.wait(min(remaining, 0.1))

    def quit(self):
        if self.process.poll() is None:
            self.send("/quit")
        self.process.wait(timeout=8)
        self.reader.join(timeout=2)
        assert self.process.returncode == 0, self.lines

    def close(self):
        if self.process.poll() is None:
            self.process.kill()
            self.process.wait(timeout=5)
        self.reader.join(timeout=2)
        self.process.stdin.close()
        self.process.stdout.close()


def free_port(ip):
    with socket.socket() as connection:
        connection.bind((ip, 0))
        return connection.getsockname()[1]


class Relay:
    def __init__(self, ip, target_port):
        self.ip = ip
        self.target_port = target_port
        self.listener = socket.socket()
        self.listener.bind((ip, 0))
        self.listener.listen()
        self.listener.settimeout(0.1)
        self.port = self.listener.getsockname()[1]
        self.running = True
        self.hold = False
        self.connections = []
        self.workers = []
        self.captures = []
        self.thread = threading.Thread(target=self._accept, daemon=True)
        self.thread.start()

    def _accept(self):
        while self.running:
            try:
                incoming, _ = self.listener.accept()
            except socket.timeout:
                continue
            except OSError:
                return
            outgoing = socket.socket()
            outgoing.bind(("127.0.0.2", 0))
            outgoing.connect((self.ip, self.target_port))
            self.connections.extend([incoming, outgoing])
            capture = [bytearray(), bytearray()]
            self.captures.append(capture)
            for source, destination, index in [(incoming, outgoing, 0), (outgoing, incoming, 1)]:
                worker = threading.Thread(target=self._copy, args=(source, destination, capture[index]), daemon=True)
                self.workers.append(worker)
                worker.start()

    def _copy(self, source, destination, capture):
        try:
            while True:
                data = source.recv(65536)
                if not data:
                    break
                capture.extend(data)
                destination.sendall(data)
        except OSError:
            pass
        finally:
            try:
                if not self.hold:
                    destination.shutdown(socket.SHUT_WR)
            except OSError:
                pass

    def close(self):
        self.running = False
        self.listener.close()
        self.thread.join(timeout=2)
        for connection in self.connections:
            try:
                connection.shutdown(socket.SHUT_RDWR)
            except OSError:
                pass
            connection.close()
        for worker in self.workers:
            worker.join(timeout=2)


def pack(fields):
    return "".join(f"{len(field)}:{field}" for field in fields).encode("ascii")


def unpack(data):
    result = []
    while data:
        length, data = data.split(b":", 1)
        size = int(length)
        assert size <= len(data)
        result.append(data[:size].decode("ascii"))
        data = data[size:]
    return result


def frames(stream):
    stream = bytes(stream)
    result = []
    while stream:
        assert len(stream) >= 4, "Truncated captured header"
        size = struct.unpack("!I", stream[:4])[0]
        assert len(stream) >= 4 + size, "Truncated captured frame"
        result.append(unpack(stream[4:4 + size]))
        stream = stream[4 + size:]
    return result


def inject(ip, port, payload):
    with socket.socket() as connection:
        connection.settimeout(2)
        connection.bind(("127.0.0.2", 0))
        connection.connect((ip, port))
        connection.sendall(payload)
        connection.shutdown(socket.SHUT_WR)
        try:
            connection.recv(1024)
        except OSError:
            pass


def run(binary):
    processes, relays = [], []
    ka, kb = "AliceMasterKey16", "BobMasterKey0016"
    new_ka, new_kb = "NewAliceKey00016", "NewBobKey0000016"
    wrong = "WrongMasterKey16"
    try:
        kdc_port, bob_port = free_port("127.0.0.1"), free_port("127.0.0.3")
        kdc = Process(binary, ["kdc", "--bind", "127.0.0.1", "--alice", "127.0.0.2", "--bob", "127.0.0.3", "--port", str(kdc_port)])
        processes.append(kdc)
        kdc.send("short")
        kdc.wait("Key must contain exactly")
        kdc.send(ka + "\r")
        kdc.send(kb)
        kdc.wait("KDC READY")
        bob = Process(binary, ["bob", "--bind", "127.0.0.3", "--kdc", "127.0.0.1", "--peer", "127.0.0.2", "--port", str(bob_port)])
        processes.append(bob)
        bob.send(kb)
        bob.wait("BOB LISTENING")
        bob.send("before authentication")
        bob.wait("Chat blocked")
        mark = bob.mark()
        bob.send("/status\r")
        bob.wait("STATUS: disconnected", mark)

        for payload in [struct.pack("!I", 65537), struct.pack("!I", 10) + b"1:x"]:
            mark = bob.mark()
            inject("127.0.0.3", bob_port, payload)
            bob.wait("HANDSHAKE REJECTED", mark)
        premature = pack(["CHAT", "not authenticated"])
        mark = bob.mark()
        inject("127.0.0.3", bob_port, struct.pack("!I", len(premature)) + premature)
        bob.wait("HANDSHAKE REJECTED", mark)
        mark = kdc.mark()
        inject("127.0.0.1", kdc_port, struct.pack("!I", 0))
        kdc.wait("KDC request rejected", mark)

        kdc_relay = Relay("127.0.0.1", kdc_port)
        bob_relay = Relay("127.0.0.3", bob_port)
        relays.extend([kdc_relay, bob_relay])
        alice = Process(binary, ["alice", "--bind", "127.0.0.2", "--kdc", "127.0.0.1", "--peer", "127.0.0.3", "--port", str(bob_relay.port), "--kdc-port", str(kdc_relay.port)])
        processes.append(alice)
        alice.send(ka)
        alice.wait("ALICE READY")
        alice.send("before authentication")
        alice.wait("Chat blocked")

        def connect(command="/connect"):
            a, b = alice.mark(), bob.mark()
            alice.send(command)
            alice.wait("SESSION ESTABLISHED", a)
            bob.wait("SESSION ESTABLISHED", b)

        def exchange(first, second):
            a, b = alice.mark(), bob.mark()
            alice.send(first)
            bob.send(second)
            bob.wait(f'RECEIVED ASCII: "{first}"', b)
            alice.wait(f'RECEIVED ASCII: "{second}"', a)

        def disconnect():
            a, b = alice.mark(), bob.mark()
            alice.send("/disconnect")
            alice.wait("DISCONNECTED", a)
            bob.wait("SESSION CLOSED", b)

        def change(peer, key):
            mark = peer.mark()
            peer.send("/key")
            peer.send(key)
            peer.wait("KEY UPDATED", mark)

        connect()
        exchange("Hello Bob", "Hello Alice")
        time.sleep(5.25)
        a, b = alice.mark(), bob.mark()
        alice.send("")
        bob.wait('RECEIVED ASCII: ""', b)
        alice.send("/send /status")
        bob.wait('RECEIVED ASCII: "/status"', b)
        exchange("A" * 4096, "Spaces and delimiters : | remain intact")
        a = alice.mark()
        alice.send("A" * 4097)
        alice.wait("Message must be ASCII", a)
        a = alice.mark()
        alice.send("caf\u00e9")
        alice.wait("Message must be ASCII", a)
        a = alice.mark()
        alice.send("/key")
        alice.wait("Disconnect and wait", a)
        connect("/rekey")
        exchange("fresh session", "fresh reply")
        disconnect()

        change(alice, wrong)
        a = alice.mark()
        alice.send("/connect")
        alice.wait("ERROR:", a)
        change(alice, ka)
        change(bob, wrong)
        a, b = alice.mark(), bob.mark()
        alice.send("/connect")
        bob.wait("HANDSHAKE REJECTED", b)
        alice.wait("ERROR:", a)
        change(bob, kb)
        connect()
        a = alice.mark()
        bob.send("/disconnect")
        alice.wait("SESSION CLOSED", a)

        for peer, identity, key in [(alice, "Alice", new_ka), (bob, "Bob", new_kb)]:
            mark = kdc.mark()
            kdc.send(f"/key {identity}")
            kdc.send(key)
            kdc.wait("KEY UPDATED", mark)
            change(peer, key)
        connect()
        exchange("rotated master keys", "no process restart")
        kdc.quit()
        exchange("KDC is offline", "direct chat still works")
        bob_relay.hold = True
        alice.quit()
        bob.quit()

        for relay in relays:
            relay.close()
        all_frames = []
        all_wire = b""
        for relay in relays:
            for capture in relay.captures:
                for stream in capture:
                    all_wire += bytes(stream)
                    all_frames.extend(frames(stream))
        for secret in [ka, kb, new_ka, new_kb, "Hello Bob", "Hello Alice", "rotated master keys"]:
            assert secret.encode() not in all_wire, f"Cleartext leaked: {secret}"
        tickets = {frame[2] for frame in all_frames if frame[0] == "2"}
        for frame in all_frames:
            if frame[0] == "3":
                assert frame[1] in tickets, "Ticket changed between steps 2 and 3"
            envelopes = frame[1:] if frame[0] in {"2", "3", "4", "5", "READY", "CHAT"} else []
            for envelope in envelopes:
                iv, ciphertext = envelope.split(":")
                assert len(iv) == 32 and len(ciphertext) >= 32 and len(ciphertext) % 32 == 0
                bytes.fromhex(iv)
                bytes.fromhex(ciphertext)
        chat = [frame for frame in all_frames if frame[0] == "CHAT"]
        assert len(chat) == 12, f"Expected 12 delivered messages, captured {len(chat)}"
        ivs = [frame[1].split(":")[0] for frame in chat]
        assert len(set(ivs)) == len(ivs), "Repeated chat IV"
        result = subprocess.run([str(binary), "alice", "--bind", "127.0.0.1", "--kdc", "127.0.0.1", "--peer", "127.0.0.3"], capture_output=True, text=True, timeout=5)
        assert result.returncode == 1 and "three distinct" in result.stdout
        print(f"PASS: integration; {len(all_frames)} captured frames; three loopback IPs; full duplex, framing rejection, key rotation, rekey, ASCII/Hex, offline KDC")
    finally:
        for relay in relays:
            relay.close()
        for process in processes:
            process.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--binary", required=True, type=Path)
    run(parser.parse_args().binary.resolve())

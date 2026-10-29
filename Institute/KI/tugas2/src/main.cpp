#include "network.hpp"

#include <atomic>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <thread>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace {
using namespace ki;
std::mutex output_mutex;

void log(const std::string& text) {
    const std::lock_guard<std::mutex> lock(output_mutex);
    std::cout << text << std::endl;
}

std::string visible(const std::string& text) {
    std::string result;
    for (const unsigned char c : text) {
        if (c == '\\') result += "\\\\";
        else if (c == '"') result += "\\\"";
        else if (c >= 32 && c <= 126) result += static_cast<char>(c);
        else result += "\\x" + hex(&c, 1);
    }
    return result;
}

bool read_line(std::string& line) {
    if (!std::getline(std::cin, line)) return false;
    if (!line.empty() && line.back() == '\r') line.pop_back();
    return true;
}

Block read_key(const std::string& prompt) {
    for (;;) {
        log(prompt + " (16 printable ASCII characters; surrounding spaces count):");
#ifdef _WIN32
        const HANDLE input = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        const bool terminal = GetConsoleMode(input, &mode) != 0;
        if (terminal) SetConsoleMode(input, mode & ~ENABLE_ECHO_INPUT);
#else
        termios mode{};
        const bool terminal = tcgetattr(STDIN_FILENO, &mode) == 0;
        if (terminal) {
            termios hidden = mode;
            hidden.c_lflag &= static_cast<tcflag_t>(~ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &hidden);
        }
#endif
        std::string value;
        const bool available = read_line(value);
#ifdef _WIN32
        if (terminal) SetConsoleMode(input, mode);
#else
        if (terminal) tcsetattr(STDIN_FILENO, TCSANOW, &mode);
#endif
        if (terminal) log("");
        if (!available) throw std::runtime_error("Input closed while reading key");
        try { return ascii_key(value); }
        catch (const std::exception& error) { log(error.what()); }
    }
}

void encrypted_log(const std::string& label, const std::string& envelope) {
    log(label + " IV=" + envelope.substr(0, 32) + " CIPHERTEXT=" + envelope.substr(33));
}

struct Options {
    std::string role, bind, kdc, peer, alice, bob;
    unsigned port = 9001, kdc_port = 9000;
};

void help() {
    log("Manual AES-128 / five-step KDC chat\n"
        "  ki_chat kdc   --bind IP --alice IP --bob IP [--port 9000]\n"
        "  ki_chat alice --bind IP --kdc IP --peer BOB_IP [--port 9001] [--kdc-port 9000]\n"
        "  ki_chat bob   --bind IP --kdc IP --peer ALICE_IP [--port 9001] [--kdc-port 9000]\n"
        "All three IP addresses must be distinct. Enter keys locally at prompts.\n"
        "KDC commands: /key Alice, /key Bob, /status, /help, /quit\n"
        "Peer commands: /connect (Alice), /rekey (Alice), /key, /disconnect, /status, /help, /quit\n"
        "Send text directly; use /send TEXT when text begins with '/'.");
}

Options parse(int argc, char** argv) {
    if (argc < 2) throw std::runtime_error("Choose kdc, alice, or bob; use --help for syntax");
    Options result;
    result.role = argv[1];
    if (result.role != "kdc" && result.role != "alice" && result.role != "bob") throw std::runtime_error("Unknown role");
    std::map<std::string, std::string> options;
    for (int i = 2; i < argc; i += 2) {
        if (i + 1 >= argc || !options.emplace(argv[i], argv[i + 1]).second) throw std::runtime_error("Missing or duplicate option");
    }
    auto take = [&options](const std::string& key, const std::string& fallback = "") {
        const auto found = options.find(key);
        if (found == options.end()) {
            if (fallback.empty()) throw std::runtime_error("Missing " + key);
            return fallback;
        }
        const std::string value = found->second;
        options.erase(found);
        return value;
    };
    result.bind = ipv4(take("--bind"));
    if (result.role == "kdc") {
        result.alice = ipv4(take("--alice"));
        result.bob = ipv4(take("--bob"));
        result.port = port_number(take("--port", "9000"));
        if (result.bind == result.alice || result.bind == result.bob || result.alice == result.bob) {
            throw std::runtime_error("KDC, Alice, and Bob require three distinct IP addresses");
        }
    } else {
        result.kdc = ipv4(take("--kdc"));
        result.peer = ipv4(take("--peer"));
        result.port = port_number(take("--port", "9001"));
        result.kdc_port = port_number(take("--kdc-port", "9000"));
        if (result.bind == result.kdc || result.bind == result.peer || result.kdc == result.peer) {
            throw std::runtime_error("KDC, Alice, and Bob require three distinct IP addresses");
        }
    }
    if (!options.empty()) throw std::runtime_error("Unknown option " + options.begin()->first);
    return result;
}

void run_kdc(const Options& options) {
    Block alice_key = read_key("KDC: enter Alice's long-term key Ka");
    Block bob_key = read_key("KDC: enter Bob's long-term key Kb");
    const auto listener = Socket::listen(options.bind, options.port);
    std::mutex keys_mutex;
    std::atomic<bool> running{true};
    std::thread server([&] {
        while (running) {
            try {
                const auto socket = listener->accept(200);
                if (!socket) continue;
                if (socket->remote_ip() != options.alice) throw std::runtime_error("Unexpected KDC requester IP");
                const Fields request = socket->receive_fields();
                Fields response;
                {
                    const std::lock_guard<std::mutex> lock(keys_mutex);
                    response = issue_session(request, alice_key, bob_key);
                }
                log("[1] Alice=" + socket->remote_ip() + " to KDC=" + socket->local_ip() + " N1=" + request[3]);
                socket->send_fields(response);
                encrypted_log("[2] Alice portion", response[1]);
                encrypted_log("[2] Bob ticket", response[2]);
            } catch (const std::exception& error) {
                if (running) log(std::string("KDC request rejected: ") + error.what());
            }
        }
    });
    log("KDC READY " + options.bind + ':' + std::to_string(options.port));
    log("Commands: /key Alice, /key Bob, /status, /help, /quit");
    try {
        std::string line;
        while (read_line(line)) {
            if (line == "/quit") break;
            if (line == "/key Alice" || line == "/key Bob") {
                const Block replacement = read_key("Enter replacement long-term key");
                const std::lock_guard<std::mutex> lock(keys_mutex);
                (line == "/key Alice" ? alice_key : bob_key) = replacement;
                log("KEY UPDATED. Update matching peer locally; existing sessions keep their session key.");
            } else if (line == "/status") {
                log("KDC listening; Alice=" + options.alice + " Bob=" + options.bob + "; keys set (hidden)");
            } else if (line == "/help") help();
            else log("Unknown command; use /help");
        }
    } catch (...) {
        running = false;
        server.join();
        throw;
    }
    running = false;
    server.join();
}

struct Channel {
    std::shared_ptr<Socket> socket;
    Block key;
    std::uint64_t outgoing = 1;
};

class Peer {
public:
    explicit Peer(Options options) : options_(std::move(options)) {}
    void run() {
        key_ = read_key(options_.role == "alice" ? "Alice: enter long-term key Ka" : "Bob: enter long-term key Kb");
        if (options_.role == "bob") {
            listener_ = Socket::listen(options_.bind, options_.port);
            receiver_ = std::thread([this] { listen_loop(); });
            log("BOB LISTENING " + options_.bind + ':' + std::to_string(options_.port));
        } else log("ALICE READY. Use /connect to begin steps 1-5.");
        log("Commands: /connect, /rekey (Alice), /key, /disconnect, /status, /help, /quit");
        try {
            std::string line;
            while (read_line(line)) {
                if (line == "/quit") break;
                try { command(line); }
                catch (const std::exception& error) { log(std::string("ERROR: ") + error.what()); }
            }
        } catch (...) {
            stop();
            throw;
        }
        stop();
    }
private:
    Options options_;
    Block key_{};
    std::mutex state_mutex_;
    std::shared_ptr<Channel> active_;
    std::shared_ptr<Socket> pending_, listener_;
    std::atomic<bool> running_{true};
    bool handshaking_ = false;
    std::thread receiver_;

    std::shared_ptr<Channel> active() {
        const std::lock_guard<std::mutex> lock(state_mutex_);
        return active_;
    }

    void disconnect() {
        const std::lock_guard<std::mutex> lock(state_mutex_);
        if (active_) active_->socket->stop();
        if (pending_) pending_->stop();
        active_.reset();
        pending_.reset();
    }

    void stop() {
        running_ = false;
        disconnect();
        if (receiver_.joinable()) receiver_.join();
    }

    void receive_chat(const std::shared_ptr<Channel>& channel) {
        std::uint64_t expected = 1;
        std::string reason;
        try {
            while (running_) {
                const Fields frame = channel->socket->receive_fields();
                require(frame, 2, "CHAT");
                const Fields message = open(frame[1], channel->key);
                require(message, 3, "message");
                if (message[1] != std::to_string(expected) || message[2].size() > MAX_MESSAGE) {
                    throw std::runtime_error("Message sequence or size mismatch");
                }
                ++expected;
                encrypted_log("RECEIVED", frame[1]);
                log("RECEIVED ASCII: \"" + visible(message[2]) + "\"");
            }
        } catch (const std::exception& error) {
            reason = error.what();
        }
        channel->socket->stop();
        bool current = false;
        {
            const std::lock_guard<std::mutex> lock(state_mutex_);
            current = active_ == channel;
            if (current) active_.reset();
        }
        if (running_ && current && !reason.empty()) log("SESSION CLOSED: " + reason);
    }

    std::shared_ptr<Channel> install(const std::shared_ptr<Socket>& socket, const Block& session_key) {
        socket->timeout(0);
        const std::lock_guard<std::mutex> lock(state_mutex_);
        if (!running_) throw std::runtime_error("Program stopping");
        if (options_.role == "bob" && pending_ != socket) throw std::runtime_error("Handshake cancelled");
        active_ = std::make_shared<Channel>(Channel{socket, session_key, 1});
        pending_.reset();
        handshaking_ = false;
        log("SESSION ESTABLISHED " + socket->local_ip() + " with " + socket->remote_ip() + "; bidirectional chat ready");
        return active_;
    }

    void listen_loop() {
        while (running_) {
            try {
                const auto socket = listener_->accept(200);
                if (!socket) continue;
                Block local_key{};
                {
                    const std::lock_guard<std::mutex> lock(state_mutex_);
                    if (!running_) break;
                    pending_ = socket;
                    handshaking_ = true;
                    local_key = key_;
                }
                if (socket->remote_ip() != options_.peer) throw std::runtime_error("Unexpected Alice IP");
                const Fields ticket = socket->receive_fields();
                const Block session_key = read_ticket(ticket, local_key);
                encrypted_log("[3] Received Bob ticket", ticket[1]);
                const std::string challenge = nonce();
                const Fields request = make_challenge(session_key, challenge);
                socket->send_fields(request);
                encrypted_log("[4] Bob challenge", request[1]);
                const Fields response = socket->receive_fields();
                check_answer(response, session_key, challenge);
                encrypted_log("[5] Verified Alice response", response[1]);
                socket->send_fields({"READY", seal({"ready"}, session_key)});
                const auto channel = install(socket, session_key);
                receive_chat(channel);
            } catch (const std::exception& error) {
                {
                    const std::lock_guard<std::mutex> lock(state_mutex_);
                    pending_.reset();
                    handshaking_ = false;
                }
                if (running_) log(std::string("HANDSHAKE REJECTED: ") + error.what());
            }
        }
    }

    void connect_session(bool rekey) {
        if (options_.role != "alice") throw std::runtime_error("Alice initiates key distribution; Bob can send after step 5");
        if (active() && !rekey) throw std::runtime_error("Session already active; use /rekey or /disconnect");
        disconnect();
        if (receiver_.joinable()) receiver_.join();
        const auto kdc = Socket::connect(options_.bind, options_.kdc, options_.kdc_port);
        const std::string n1 = nonce();
        kdc->send_fields({"1", "Alice", "Bob", n1});
        log("[1] Alice=" + kdc->local_ip() + " to KDC=" + kdc->remote_ip() + " N1=" + n1);
        const Fields response = kdc->receive_fields();
        const Session session = read_session(response, key_, n1);
        encrypted_log("[2] Validated Alice portion", response[1]);
        const auto bob = Socket::connect(options_.bind, options_.peer, options_.port);
        bob->send_fields({"3", session.ticket});
        encrypted_log("[3] Forwarded unchanged Bob ticket", session.ticket);
        const Fields challenge = bob->receive_fields();
        const Fields answer = answer_challenge(challenge, session.key);
        encrypted_log("[4] Received Bob challenge", challenge[1]);
        bob->send_fields(answer);
        encrypted_log("[5] Sent Alice response", answer[1]);
        const Fields ready = bob->receive_fields();
        require(ready, 2, "READY");
        require(open(ready[1], session.key), 1, "ready");
        const auto channel = install(bob, session.key);
        receiver_ = std::thread([this, channel] { receive_chat(channel); });
    }

    void command(const std::string& line) {
        if (line == "/help") { help(); return; }
        if (line == "/connect" || line == "/rekey") { connect_session(line == "/rekey"); return; }
        if (line == "/disconnect") { disconnect(); log("DISCONNECTED"); return; }
        if (line == "/status") {
            const std::lock_guard<std::mutex> lock(state_mutex_);
            log(active_ ? "STATUS: authenticated session active" : (handshaking_ ? "STATUS: handshaking" : "STATUS: disconnected"));
            return;
        }
        if (line == "/key") {
            const std::lock_guard<std::mutex> lock(state_mutex_);
            if (active_ || handshaking_) throw std::runtime_error("Disconnect and wait for pending handshake before changing key");
            key_ = read_key("Enter replacement long-term key; also update KDC locally");
            log("KEY UPDATED; start a fresh session");
            return;
        }
        const bool explicit_send = line.rfind("/send ", 0) == 0;
        if (!explicit_send && !line.empty() && line[0] == '/') throw std::runtime_error("Unknown command; use /help or /send TEXT");
        const std::string text = explicit_send ? line.substr(6) : line;
        if (!is_ascii(text) || text.size() > MAX_MESSAGE) throw std::runtime_error("Message must be ASCII and at most 4096 bytes");
        const auto channel = active();
        if (!channel) throw std::runtime_error("Chat blocked: complete steps 1-5 first");
        const std::string envelope = seal({"message", std::to_string(channel->outgoing), text}, channel->key);
        try { channel->socket->send_fields({"CHAT", envelope}); }
        catch (...) { channel->socket->stop(); throw; }
        ++channel->outgoing;
        log("SENT ASCII: \"" + visible(text) + "\"");
        encrypted_log("SENT", envelope);
    }
};
}

int main(int argc, char** argv) {
    try {
        if (argc == 2 && std::string(argv[1]) == "--help") { help(); return 0; }
        const NetworkRuntime network;
        const Options options = parse(argc, argv);
        if (options.role == "kdc") run_kdc(options);
        else Peer(options).run();
        return 0;
    } catch (const std::exception& error) {
        log(std::string("ERROR: ") + error.what());
        return 1;
    }
}

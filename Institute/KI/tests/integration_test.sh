#!/usr/bin/env bash
set -u

cd "$(dirname "$0")/.."

port=18081
server_log="$(mktemp)"
trap 'rm -f "$server_log"' EXIT

(printf '%s\n' 'Balasan dari server' | ./server "$port") >"$server_log" 2>&1 &
server_pid=$!
sleep 1

client_output="$(printf '%s\n' 'Halo dari client' '/quit' | ./client 127.0.0.1 "$port")"
client_status=$?
wait "$server_pid"
server_status=$?
server_output="$(cat "$server_log")"

printf '%s\n' "$client_output"
printf '%s\n' "$server_output"

if [[ $client_status -ne 0 || $server_status -ne 0 ]]; then
    echo "FAIL: proses server/client mengembalikan error" >&2
    exit 1
fi

if [[ "$client_output" != *"Server      : Balasan dari server"* ]]; then
    echo "FAIL: client tidak menerima balasan server" >&2
    exit 1
fi

if [[ "$server_output" != *"Client      : Halo dari client"* ||
      "$server_output" != *"Client      : /quit"* ]]; then
    echo "FAIL: server tidak menerima pesan client" >&2
    exit 1
fi

echo "PASS: komunikasi TCP dua arah berhasil"

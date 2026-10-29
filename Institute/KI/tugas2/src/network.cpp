#include "network.hpp"

#include <array>
#include <cerrno>
#include <charconv>
#include <stdexcept>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
using NativeSocket = SOCKET;
static constexpr NativeSocket invalid_socket = INVALID_SOCKET;
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
using NativeSocket = int;
static constexpr NativeSocket invalid_socket = -1;
#endif

namespace ki {
namespace {
NativeSocket native(std::uintptr_t handle) { return static_cast<NativeSocket>(handle); }
int last_error() {
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
}
bool interrupted() {
#ifdef _WIN32
    return last_error() == WSAEINTR;
#else
    return errno == EINTR;
#endif
}
[[noreturn]] void fail(const std::string& action) {
    throw std::runtime_error(action + " failed (socket error " + std::to_string(last_error()) + ')');
}
sockaddr_in address(const std::string& ip, unsigned port) {
    sockaddr_in result{};
    result.sin_family = AF_INET;
    result.sin_port = htons(static_cast<std::uint16_t>(port));
    if (inet_pton(AF_INET, ip.c_str(), &result.sin_addr) != 1) throw std::runtime_error("Invalid IPv4 address");
    return result;
}
std::shared_ptr<Socket> create_socket() {
    const auto handle = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (handle == invalid_socket) fail("Create socket");
    return std::make_shared<Socket>(static_cast<std::uintptr_t>(handle));
}
void nonblocking(NativeSocket socket, bool enabled) {
#ifdef _WIN32
    u_long mode = enabled ? 1 : 0;
    if (ioctlsocket(socket, FIONBIO, &mode) != 0) fail("Socket mode");
#else
    const int flags = fcntl(socket, F_GETFL, 0);
    if (flags < 0 || fcntl(socket, F_SETFL, enabled ? flags | O_NONBLOCK : flags & ~O_NONBLOCK) < 0) fail("Socket mode");
#endif
}
bool ready(NativeSocket socket, unsigned wait_ms, bool writing) {
    fd_set selected;
    FD_ZERO(&selected);
    FD_SET(socket, &selected);
    timeval timeout{static_cast<long>(wait_ms / 1000), static_cast<long>((wait_ms % 1000) * 1000)};
    const int result = select(static_cast<int>(socket + 1), writing ? nullptr : &selected,
                              writing ? &selected : nullptr, nullptr, &timeout);
    if (result < 0) {
        if (interrupted()) return false;
        fail("Select socket");
    }
    return result > 0;
}
}

NetworkRuntime::NetworkRuntime() {
#ifdef _WIN32
    WSADATA data{};
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) throw std::runtime_error("Winsock initialization failed");
#endif
}
NetworkRuntime::~NetworkRuntime() {
#ifdef _WIN32
    WSACleanup();
#endif
}
Socket::Socket(std::uintptr_t handle) : handle_(handle) {}
Socket::~Socket() {
#ifdef _WIN32
    closesocket(native(handle_));
#else
    ::close(native(handle_));
#endif
}

void Socket::timeout(unsigned milliseconds) {
    receive_timeout_ = milliseconds;
#ifdef _WIN32
    DWORD value = milliseconds;
#else
    timeval value{static_cast<long>(milliseconds / 1000), static_cast<long>((milliseconds % 1000) * 1000)};
#endif
    for (const auto option : {SO_RCVTIMEO, SO_SNDTIMEO}) {
#ifdef _WIN32
        if (option == SO_SNDTIMEO) value = 5000;
#else
        if (option == SO_SNDTIMEO) value = timeval{5, 0};
#endif
        if (setsockopt(native(handle_), SOL_SOCKET, option, reinterpret_cast<const char*>(&value), sizeof(value)) != 0) {
            fail("Set socket timeout");
        }
    }
}

void Socket::stop() {
    stopped_ = true;
#ifdef _WIN32
    shutdown(native(handle_), SD_BOTH);
#else
    shutdown(native(handle_), SHUT_RDWR);
#endif
}

std::shared_ptr<Socket> Socket::listen(const std::string& local_ip, unsigned port) {
    auto socket = create_socket();
    const int enabled = 1;
#ifdef _WIN32
    const int reuse_option = SO_EXCLUSIVEADDRUSE;
#else
    const int reuse_option = SO_REUSEADDR;
#endif
    if (setsockopt(native(socket->handle_), SOL_SOCKET, reuse_option,
                   reinterpret_cast<const char*>(&enabled), sizeof(enabled)) != 0) fail("Set listener option");
    const auto local = address(local_ip, port);
    if (::bind(native(socket->handle_), reinterpret_cast<const sockaddr*>(&local), sizeof(local)) != 0) fail("Bind listener");
    if (::listen(native(socket->handle_), 8) != 0) fail("Listen");
    return socket;
}

std::shared_ptr<Socket> Socket::connect(const std::string& local_ip, const std::string& remote_ip, unsigned port) {
    auto socket = create_socket();
    const auto local = address(local_ip, 0);
    const auto remote = address(remote_ip, port);
    const NativeSocket handle = native(socket->handle_);
    if (::bind(handle, reinterpret_cast<const sockaddr*>(&local), sizeof(local)) != 0) fail("Bind client");
    nonblocking(handle, true);
    const int result = ::connect(handle, reinterpret_cast<const sockaddr*>(&remote), sizeof(remote));
    if (result != 0) {
        const int error = last_error();
#ifdef _WIN32
        if (error != WSAEWOULDBLOCK && error != WSAEINPROGRESS) fail("Connect");
#else
        if (error != EINPROGRESS) fail("Connect");
#endif
        fd_set writes, errors;
        FD_ZERO(&writes);
        FD_ZERO(&errors);
        FD_SET(handle, &writes);
        FD_SET(handle, &errors);
        timeval wait{5, 0};
        if (select(static_cast<int>(handle + 1), nullptr, &writes, &errors, &wait) <= 0) {
            throw std::runtime_error("Connection timed out or was interrupted");
        }
        int socket_error = 0;
#ifdef _WIN32
        int length = sizeof(socket_error);
#else
        socklen_t length = sizeof(socket_error);
#endif
        if (getsockopt(handle, SOL_SOCKET, SO_ERROR, reinterpret_cast<char*>(&socket_error), &length) != 0) fail("Check connection");
        if (socket_error != 0) throw std::runtime_error("Connect failed (socket error " + std::to_string(socket_error) + ')');
    }
    nonblocking(handle, false);
    socket->timeout(5000);
    return socket;
}

std::shared_ptr<Socket> Socket::accept(unsigned wait_ms) {
    if (!ready(native(handle_), wait_ms, false)) return nullptr;
    const auto accepted = ::accept(native(handle_), nullptr, nullptr);
    if (accepted == invalid_socket) fail("Accept");
    auto result = std::make_shared<Socket>(static_cast<std::uintptr_t>(accepted));
    result->timeout(5000);
    return result;
}

void Socket::send_bytes(const std::uint8_t* data, std::size_t size) {
    while (size) {
#if defined(_WIN32)
        const int result = ::send(native(handle_), reinterpret_cast<const char*>(data), static_cast<int>(size), 0);
#else
        const auto result = ::send(native(handle_), data, size, MSG_NOSIGNAL);
#endif
        if (result < 0 && interrupted()) continue;
        if (result <= 0) fail("Send");
        data += result;
        size -= static_cast<std::size_t>(result);
    }
}

bool Socket::receive_bytes(std::uint8_t* data, std::size_t size) {
    std::size_t received = 0;
    while (received < size) {
        if (stopped_) throw std::runtime_error("Connection closed locally");
        if (!receive_timeout_ && !ready(native(handle_), 200, false)) continue;
        const auto result = ::recv(native(handle_), reinterpret_cast<char*>(data + received),
                                   static_cast<int>(size - received), 0);
        if (result < 0 && interrupted()) continue;
        if (result < 0) fail("Receive (timeout or network error)");
        if (result == 0) {
            if (received == 0) return false;
            throw std::runtime_error("Truncated TCP frame");
        }
        received += static_cast<std::size_t>(result);
    }
    return true;
}

void Socket::send_fields(const Fields& fields) {
    const std::string payload = pack(fields);
    const auto length = static_cast<std::uint32_t>(payload.size());
    const std::array<std::uint8_t, 4> header{
        static_cast<std::uint8_t>(length >> 24), static_cast<std::uint8_t>(length >> 16),
        static_cast<std::uint8_t>(length >> 8), static_cast<std::uint8_t>(length)};
    const std::lock_guard<std::mutex> lock(send_mutex_);
    send_bytes(header.data(), header.size());
    send_bytes(reinterpret_cast<const std::uint8_t*>(payload.data()), payload.size());
}

Fields Socket::receive_fields() {
    std::array<std::uint8_t, 4> header{};
    if (!receive_bytes(header.data(), header.size())) throw std::runtime_error("Peer disconnected");
    std::uint32_t length = 0;
    for (const auto byte : header) length = (length << 8) | byte;
    if (length == 0 || length > MAX_FRAME) throw std::runtime_error("Invalid TCP frame length");
    std::string payload(length, '\0');
    if (!receive_bytes(reinterpret_cast<std::uint8_t*>(&payload[0]), payload.size())) {
        throw std::runtime_error("Truncated TCP payload");
    }
    return unpack(payload);
}

std::string Socket::remote_ip() const {
    sockaddr_in remote{};
#ifdef _WIN32
    int length = sizeof(remote);
#else
    socklen_t length = sizeof(remote);
#endif
    if (getpeername(native(handle_), reinterpret_cast<sockaddr*>(&remote), &length) != 0) fail("Read peer address");
    std::array<char, INET_ADDRSTRLEN> text{};
    if (!inet_ntop(AF_INET, &remote.sin_addr, text.data(), static_cast<unsigned>(text.size()))) fail("Format peer address");
    return text.data();
}

std::string Socket::local_ip() const {
    sockaddr_in local{};
#ifdef _WIN32
    int length = sizeof(local);
#else
    socklen_t length = sizeof(local);
#endif
    if (getsockname(native(handle_), reinterpret_cast<sockaddr*>(&local), &length) != 0) fail("Read local address");
    std::array<char, INET_ADDRSTRLEN> text{};
    if (!inet_ntop(AF_INET, &local.sin_addr, text.data(), static_cast<unsigned>(text.size()))) fail("Format local address");
    return text.data();
}

std::string ipv4(const std::string& value) {
    const auto parsed = address(value, 0);
    const auto host = ntohl(parsed.sin_addr.s_addr);
    if (host == 0 || host == 0xffffffffU || (host >> 24) >= 224) {
        throw std::runtime_error("Use a concrete unicast IPv4 address");
    }
    std::array<char, INET_ADDRSTRLEN> text{};
    if (!inet_ntop(AF_INET, &parsed.sin_addr, text.data(), static_cast<unsigned>(text.size()))) fail("Format address");
    return text.data();
}

unsigned port_number(const std::string& value) {
    unsigned result = 0;
    const auto parsed = std::from_chars(value.data(), value.data() + value.size(), result);
    if (parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size() || result == 0 || result > 65535) {
        throw std::runtime_error("Port must be between 1 and 65535");
    }
    return result;
}
}

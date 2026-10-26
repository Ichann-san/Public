#pragma once

#include "protocol.hpp"

#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

namespace ki {
class NetworkRuntime {
public:
    NetworkRuntime();
    ~NetworkRuntime();
    NetworkRuntime(const NetworkRuntime&) = delete;
    NetworkRuntime& operator=(const NetworkRuntime&) = delete;
};

class Socket {
public:
    explicit Socket(std::uintptr_t handle);
    ~Socket();
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;
    void timeout(unsigned milliseconds);
    void stop();
    void send_fields(const Fields& fields);
    Fields receive_fields();
    std::string remote_ip() const;
    std::string local_ip() const;
    static std::shared_ptr<Socket> connect(const std::string& local_ip, const std::string& remote_ip, unsigned port);
    static std::shared_ptr<Socket> listen(const std::string& local_ip, unsigned port);
    std::shared_ptr<Socket> accept(unsigned wait_ms);
private:
    std::uintptr_t handle_;
    std::mutex send_mutex_;
    void send_bytes(const std::uint8_t* data, std::size_t size);
    bool receive_bytes(std::uint8_t* data, std::size_t size);
};

std::string ipv4(const std::string& value);
unsigned port_number(const std::string& value);
}

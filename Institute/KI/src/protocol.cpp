#include "protocol.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>

#include <algorithm>
#include <array>
#include <cerrno>
#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

namespace protocol {
namespace {

constexpr std::uint32_t MAX_PAYLOAD_SIZE = 1024 * 1024;

void send_all(int socket_fd, const std::uint8_t* data, std::size_t size) {
    std::size_t sent = 0;
    while (sent < size) {
        const ssize_t result = send(socket_fd, data + sent, size - sent, 0);
        if (result < 0 && errno == EINTR) {
            continue;
        }
        if (result <= 0) {
            throw std::runtime_error("Gagal mengirim data");
        }
        sent += static_cast<std::size_t>(result);
    }
}

bool receive_exact(int socket_fd, std::uint8_t* data, std::size_t size) {
    std::size_t received = 0;
    while (received < size) {
        const ssize_t result = recv(socket_fd, data + received, size - received, 0);
        if (result < 0 && errno == EINTR) {
            continue;
        }
        if (result < 0) {
            throw std::runtime_error("Gagal menerima data");
        }
        if (result == 0) {
            if (received == 0) {
                return false;
            }
            throw std::runtime_error("Koneksi terputus di tengah pesan");
        }
        received += static_cast<std::size_t>(result);
    }
    return true;
}

des::Block make_iv() {
    std::random_device random;
    des::Block iv{};
    for (auto& byte : iv) {
        byte = static_cast<std::uint8_t>(random());
    }
    return iv;
}

}  // namespace

void send_message(int socket_fd, const std::string& plaintext) {
    const des::Block iv = make_iv();
    const auto ciphertext = des::encrypt_cbc(plaintext, SHARED_KEY, iv);
    const std::uint32_t payload_size = static_cast<std::uint32_t>(iv.size() + ciphertext.size());
    const std::uint32_t network_size = htonl(payload_size);

    send_all(socket_fd, reinterpret_cast<const std::uint8_t*>(&network_size), sizeof(network_size));
    send_all(socket_fd, iv.data(), iv.size());
    send_all(socket_fd, ciphertext.data(), ciphertext.size());

    std::cout << "  IV         : " << des::to_hex(iv) << '\n';
    std::cout << "  Ciphertext : " << des::to_hex(ciphertext) << '\n';
}

bool receive_message(int socket_fd, std::string& plaintext) {
    std::uint32_t network_size = 0;
    if (!receive_exact(socket_fd,
                       reinterpret_cast<std::uint8_t*>(&network_size),
                       sizeof(network_size))) {
        return false;
    }

    const std::uint32_t payload_size = ntohl(network_size);
    if (payload_size < 16 || payload_size > MAX_PAYLOAD_SIZE ||
        (payload_size - 8) % 8 != 0) {
        throw std::runtime_error("Ukuran payload tidak valid");
    }

    std::vector<std::uint8_t> payload(payload_size);
    if (!receive_exact(socket_fd, payload.data(), payload.size())) {
        throw std::runtime_error("Koneksi terputus sebelum payload diterima");
    }

    des::Block iv{};
    std::copy_n(payload.begin(), 8, iv.begin());
    std::vector<std::uint8_t> ciphertext(payload.begin() + 8, payload.end());

    std::cout << "  IV diterima : " << des::to_hex(iv) << '\n';
    std::cout << "  Ciphertext   : " << des::to_hex(ciphertext) << '\n';
    plaintext = des::decrypt_cbc(ciphertext, SHARED_KEY, iv);
    return true;
}

}  // namespace protocol

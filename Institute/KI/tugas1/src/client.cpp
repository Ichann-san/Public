#include "protocol.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

int parse_port(int argc, char* argv[]) {
    const int port = argc > 2 ? std::stoi(argv[2]) : 8080;
    if (port < 1 || port > 65535) {
        throw std::runtime_error("Port harus berada di antara 1 dan 65535");
    }
    return port;
}

}  // namespace

int main(int argc, char* argv[]) {
    int socket_fd = -1;
    try {
        const std::string server_ip = argc > 1 ? argv[1] : "127.0.0.1";
        const int port = parse_port(argc, argv);

        socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_fd < 0) {
            throw std::runtime_error("Gagal membuat socket");
        }

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_port = htons(static_cast<std::uint16_t>(port));
        if (inet_pton(AF_INET, server_ip.c_str(), &address.sin_addr) != 1) {
            throw std::runtime_error("Alamat IPv4 tidak valid");
        }
        if (connect(socket_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0) {
            throw std::runtime_error("Gagal terhubung ke server");
        }

        std::cout << "Terhubung ke " << server_ip << ':' << port << ".\n";
        while (true) {
            std::cout << "Anda        : ";
            std::string message;
            if (!std::getline(std::cin, message)) {
                message = "/quit";
            }
            protocol::send_message(socket_fd, message);
            if (message == "/quit") {
                break;
            }

            std::string reply;
            if (!protocol::receive_message(socket_fd, reply)) {
                std::cout << "Server menutup koneksi.\n";
                break;
            }
            std::cout << "Server      : " << reply << '\n';
            if (reply == "/quit") {
                break;
            }
        }

        close(socket_fd);
        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        if (socket_fd >= 0) close(socket_fd);
        return EXIT_FAILURE;
    }
}

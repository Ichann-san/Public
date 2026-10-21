#include "protocol.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

int parse_port(int argc, char* argv[]) {
    const int port = argc > 1 ? std::stoi(argv[1]) : 8080;
    if (port < 1 || port > 65535) {
        throw std::runtime_error("Port harus berada di antara 1 dan 65535");
    }
    return port;
}

}  // namespace

int main(int argc, char* argv[]) {
    int listen_fd = -1;
    int client_fd = -1;
    try {
        const int port = parse_port(argc, argv);
        listen_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (listen_fd < 0) {
            throw std::runtime_error("Gagal membuat socket");
        }

        const int reuse = 1;
        setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(INADDR_ANY);
        address.sin_port = htons(static_cast<std::uint16_t>(port));

        if (bind(listen_fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) < 0 ||
            listen(listen_fd, 1) < 0) {
            throw std::runtime_error("Gagal bind/listen pada port " + std::to_string(port));
        }

        std::cout << "Server menunggu koneksi pada port " << port << "...\n";
        client_fd = accept(listen_fd, nullptr, nullptr);
        if (client_fd < 0) {
            throw std::runtime_error("Gagal menerima koneksi");
        }
        std::cout << "Client terhubung. Menunggu pesan...\n";

        while (true) {
            std::string incoming;
            if (!protocol::receive_message(client_fd, incoming)) {
                std::cout << "Client menutup koneksi.\n";
                break;
            }
            std::cout << "Client      : " << incoming << '\n';
            if (incoming == "/quit") {
                break;
            }

            std::cout << "Anda        : ";
            std::string reply;
            if (!std::getline(std::cin, reply)) {
                reply = "/quit";
            }
            protocol::send_message(client_fd, reply);
            if (reply == "/quit") {
                break;
            }
        }

        close(client_fd);
        close(listen_fd);
        return EXIT_SUCCESS;
    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << '\n';
        if (client_fd >= 0) close(client_fd);
        if (listen_fd >= 0) close(listen_fd);
        return EXIT_FAILURE;
    }
}

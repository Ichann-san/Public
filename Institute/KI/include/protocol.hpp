#pragma once

#include "des.hpp"

#include <string>

namespace protocol {

constexpr des::Block SHARED_KEY = {'K', 'u', 'n', 'c', 'i', 'D', 'E', 'S'};

// Mengembalikan false jika peer menutup koneksi dengan normal.
bool receive_message(int socket_fd, std::string& plaintext);
void send_message(int socket_fd, const std::string& plaintext);

}  // namespace protocol

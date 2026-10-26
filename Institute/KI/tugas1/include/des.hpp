#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace des {

using Block = std::array<std::uint8_t, 8>;

Block encrypt_block(const Block& plaintext, const Block& key);
Block decrypt_block(const Block& ciphertext, const Block& key);

std::vector<std::uint8_t> encrypt_cbc(const std::string& plaintext,
                                      const Block& key,
                                      const Block& iv);
std::string decrypt_cbc(const std::vector<std::uint8_t>& ciphertext,
                        const Block& key,
                        const Block& iv);

std::string to_hex(const std::uint8_t* data, std::size_t size);
std::string to_hex(const std::vector<std::uint8_t>& data);
std::string to_hex(const Block& data);

}  // namespace des

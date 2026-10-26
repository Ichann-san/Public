#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace ki {
using Block = std::array<std::uint8_t, 16>;
using Bytes = std::vector<std::uint8_t>;

class AES128 {
public:
    explicit AES128(const Block& key);
    Block encrypt(Block state) const;
    Block decrypt(Block state) const;
private:
    std::array<std::uint8_t, 176> round_keys_{};
    void add_key(Block& state, unsigned round) const;
};

bool is_ascii(const std::string& text);
Block ascii_key(const std::string& text);
std::string hex(const std::uint8_t* data, std::size_t size);
std::string hex(const Bytes& bytes);
std::string hex(const Block& block);
Bytes unhex(const std::string& text);
Bytes cbc_encrypt(const Bytes& plaintext, const Block& key, const Block& iv);
Bytes cbc_decrypt(const Bytes& ciphertext, const Block& key, const Block& iv);
}

#include "aes.hpp"

#include <algorithm>
#include <stdexcept>

namespace ki {
namespace {
std::uint8_t multiply(std::uint8_t a, std::uint8_t b) {
    std::uint8_t result = 0;
    for (unsigned i = 0; i < 8; ++i) {
        if (b & 1) result ^= a;
        const bool high = (a & 0x80) != 0;
        a = static_cast<std::uint8_t>(a << 1);
        if (high) a ^= 0x1b;
        b >>= 1;
    }
    return result;
}

std::uint8_t rotate(std::uint8_t value, unsigned shift) {
    return static_cast<std::uint8_t>((value << shift) | (value >> (8 - shift)));
}

struct Tables {
    std::array<std::uint8_t, 256> forward{};
    std::array<std::uint8_t, 256> inverse{};
    Tables() {
        for (unsigned i = 0; i < 256; ++i) {
            std::uint8_t base = static_cast<std::uint8_t>(i);
            std::uint8_t value = 1;
            unsigned exponent = 254;
            while (exponent) {
                if (exponent & 1) value = multiply(value, base);
                base = multiply(base, base);
                exponent >>= 1;
            }
            if (i == 0) value = 0;
            const auto substituted = static_cast<std::uint8_t>(
                value ^ rotate(value, 1) ^ rotate(value, 2) ^
                rotate(value, 3) ^ rotate(value, 4) ^ 0x63);
            forward[i] = substituted;
            inverse[substituted] = static_cast<std::uint8_t>(i);
        }
    }
};

const Tables& tables() {
    static const Tables result;
    return result;
}

void substitute(Block& state, bool inverse) {
    const auto& table = inverse ? tables().inverse : tables().forward;
    for (auto& byte : state) byte = table[byte];
}

void shift_rows(Block& state, bool inverse) {
    const Block original = state;
    for (unsigned row = 0; row < 4; ++row) {
        for (unsigned column = 0; column < 4; ++column) {
            const unsigned source = (column + (inverse ? 4 - row : row)) % 4;
            state[4 * column + row] = original[4 * source + row];
        }
    }
}

void mix_columns(Block& state, bool inverse) {
    const std::array<std::uint8_t, 4> coefficients = inverse
        ? std::array<std::uint8_t, 4>{14, 11, 13, 9}
        : std::array<std::uint8_t, 4>{2, 3, 1, 1};
    const Block original = state;
    for (unsigned column = 0; column < 4; ++column) {
        for (unsigned row = 0; row < 4; ++row) {
            std::uint8_t value = 0;
            for (unsigned k = 0; k < 4; ++k) {
                value ^= multiply(original[4 * column + k], coefficients[(k + 4 - row) % 4]);
            }
            state[4 * column + row] = value;
        }
    }
}
}

AES128::AES128(const Block& key) {
    std::copy(key.begin(), key.end(), round_keys_.begin());
    std::size_t generated = 16;
    std::uint8_t rcon = 1;
    while (generated < round_keys_.size()) {
        std::array<std::uint8_t, 4> word{};
        std::copy_n(round_keys_.begin() + static_cast<std::ptrdiff_t>(generated - 4), 4, word.begin());
        if (generated % 16 == 0) {
            std::rotate(word.begin(), word.begin() + 1, word.end());
            for (auto& byte : word) byte = tables().forward[byte];
            word[0] ^= rcon;
            rcon = multiply(rcon, 2);
        }
        for (unsigned i = 0; i < 4; ++i) {
            round_keys_[generated] = round_keys_[generated - 16] ^ word[i];
            ++generated;
        }
    }
}

void AES128::add_key(Block& state, unsigned round) const {
    for (unsigned i = 0; i < 16; ++i) state[i] ^= round_keys_[16 * round + i];
}

Block AES128::encrypt(Block state) const {
    add_key(state, 0);
    for (unsigned round = 1; round <= 10; ++round) {
        substitute(state, false);
        shift_rows(state, false);
        if (round != 10) mix_columns(state, false);
        add_key(state, round);
    }
    return state;
}

Block AES128::decrypt(Block state) const {
    add_key(state, 10);
    for (int round = 9; round >= 0; --round) {
        shift_rows(state, true);
        substitute(state, true);
        add_key(state, static_cast<unsigned>(round));
        if (round != 0) mix_columns(state, true);
    }
    return state;
}

bool is_ascii(const std::string& text) {
    return std::all_of(text.begin(), text.end(), [](unsigned char c) { return c <= 127; });
}

Block ascii_key(const std::string& text) {
    if (text.size() != 16 || !std::all_of(text.begin(), text.end(),
            [](unsigned char c) { return c >= 32 && c <= 126; })) {
        throw std::runtime_error("Key must contain exactly 16 printable ASCII characters");
    }
    Block result{};
    std::copy(text.begin(), text.end(), result.begin());
    return result;
}

std::string hex(const std::uint8_t* data, std::size_t size) {
    static constexpr char digits[] = "0123456789abcdef";
    std::string result;
    result.reserve(size * 2);
    for (std::size_t i = 0; i < size; ++i) {
        result += digits[data[i] >> 4];
        result += digits[data[i] & 15];
    }
    return result;
}

std::string hex(const Bytes& bytes) { return hex(bytes.data(), bytes.size()); }
std::string hex(const Block& block) { return hex(block.data(), block.size()); }

Bytes unhex(const std::string& text) {
    if (text.size() % 2 != 0) throw std::runtime_error("Hex must contain complete bytes");
    auto digit = [](char c) -> unsigned {
        if (c >= '0' && c <= '9') return static_cast<unsigned>(c - '0');
        if (c >= 'a' && c <= 'f') return static_cast<unsigned>(c - 'a' + 10);
        if (c >= 'A' && c <= 'F') return static_cast<unsigned>(c - 'A' + 10);
        throw std::runtime_error("Invalid hexadecimal character");
    };
    Bytes result;
    result.reserve(text.size() / 2);
    for (std::size_t i = 0; i < text.size(); i += 2) {
        result.push_back(static_cast<std::uint8_t>((digit(text[i]) << 4) | digit(text[i + 1])));
    }
    return result;
}

Bytes cbc_encrypt(const Bytes& plaintext, const Block& key, const Block& iv) {
    Bytes padded = plaintext;
    const auto padding = static_cast<std::uint8_t>(16 - padded.size() % 16);
    padded.insert(padded.end(), padding, padding);
    const AES128 aes(key);
    Block previous = iv;
    for (std::size_t offset = 0; offset < padded.size(); offset += 16) {
        Block block{};
        for (unsigned i = 0; i < 16; ++i) block[i] = padded[offset + i] ^ previous[i];
        previous = aes.encrypt(block);
        std::copy(previous.begin(), previous.end(), padded.begin() + static_cast<std::ptrdiff_t>(offset));
    }
    return padded;
}

Bytes cbc_decrypt(const Bytes& ciphertext, const Block& key, const Block& iv) {
    if (ciphertext.empty() || ciphertext.size() % 16 != 0) {
        throw std::runtime_error("Ciphertext must contain whole AES blocks");
    }
    Bytes result(ciphertext.size());
    const AES128 aes(key);
    Block previous = iv;
    for (std::size_t offset = 0; offset < ciphertext.size(); offset += 16) {
        Block block{};
        std::copy_n(ciphertext.begin() + static_cast<std::ptrdiff_t>(offset), 16, block.begin());
        const Block decrypted = aes.decrypt(block);
        for (unsigned i = 0; i < 16; ++i) result[offset + i] = decrypted[i] ^ previous[i];
        previous = block;
    }
    const unsigned padding = result.back();
    if (padding == 0 || padding > 16 || !std::all_of(result.end() - padding, result.end(),
            [padding](std::uint8_t c) { return c == padding; })) {
        throw std::runtime_error("Invalid encrypted payload");
    }
    result.resize(result.size() - padding);
    return result;
}
}

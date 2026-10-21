#include "des.hpp"

#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

bool test_known_vector() {
    const des::Block key = {0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1};
    const des::Block plaintext = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    const des::Block expected = {0x85, 0xe8, 0x13, 0x54, 0x0f, 0x0a, 0xb4, 0x05};
    const auto encrypted = des::encrypt_block(plaintext, key);
    return encrypted == expected && des::decrypt_block(encrypted, key) == plaintext;
}

bool test_cbc_round_trip() {
    const des::Block key = {'K', 'u', 'n', 'c', 'i', 'D', 'E', 'S'};
    const des::Block iv = {0, 1, 2, 3, 4, 5, 6, 7};
    const std::vector<std::string> messages = {
        "", "Halo", "12345678", "Pesan lebih dari satu blok!", "Spasi & tanda baca: aman?"};
    for (const auto& message : messages) {
        const auto encrypted = des::encrypt_cbc(message, key, iv);
        if (des::decrypt_cbc(encrypted, key, iv) != message) {
            return false;
        }
    }
    return true;
}

}  // namespace

int main() {
    if (!test_known_vector()) {
        std::cerr << "FAIL: DES known-answer test\n";
        return 1;
    }
    if (!test_cbc_round_trip()) {
        std::cerr << "FAIL: CBC round-trip test\n";
        return 1;
    }
    std::cout << "PASS: seluruh pengujian DES berhasil\n";
    return 0;
}

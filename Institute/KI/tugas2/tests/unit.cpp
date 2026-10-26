#include "protocol.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <stdexcept>

namespace {
using namespace ki;
unsigned checks = 0;

void check(bool condition, const std::string& label) {
    ++checks;
    if (!condition) throw std::runtime_error(label);
}

void rejects(const std::function<void()>& action, const std::string& label) {
    bool rejected = false;
    try { action(); } catch (const std::exception&) { rejected = true; }
    check(rejected, label);
}

Block block(const std::string& text) {
    const Bytes bytes = unhex(text);
    if (bytes.size() != 16) throw std::runtime_error("Bad test block");
    Block result{};
    std::copy(bytes.begin(), bytes.end(), result.begin());
    return result;
}

void aes_vectors() {
    const Block key = block("000102030405060708090a0b0c0d0e0f");
    const Block plaintext = block("00112233445566778899aabbccddeeff");
    const Block ciphertext = block("69c4e0d86a7b0430d8cdb78070b4c55a");
    check(AES128(key).encrypt(plaintext) == ciphertext, "FIPS 197 AES encryption");
    check(AES128(key).decrypt(ciphertext) == plaintext, "FIPS 197 AES decryption");
    const Block zero{};
    check(hex(AES128(zero).encrypt(zero)) == "66e94bd4ef8a2c3b884cfa59ca342b2e", "AES zero vector");

    const Block cbc_key = block("2b7e151628aed2a6abf7158809cf4f3c");
    const Block iv = block("000102030405060708090a0b0c0d0e0f");
    const Bytes input = unhex("6bc1bee22e409f96e93d7e117393172a"
                              "ae2d8a571e03ac9c9eb76fac45af8e51"
                              "30c81c46a35ce411e5fbc1191a0a52ef"
                              "f69f2445df4f9b17ad2b417be66c3710");
    const std::string expected = "7649abac8119b246cee98e9b12e9197d"
                                 "5086cb9b507219ee95db113a917678b2"
                                 "73bed6b8e3c1743b7116e69e22229516"
                                 "3ff1caa1681fac09120eca307586e1a7";
    const Bytes encrypted = cbc_encrypt(input, cbc_key, iv);
    check(hex(encrypted).substr(0, expected.size()) == expected, "SP 800-38A four CBC blocks");
    check(encrypted.size() == input.size() + 16, "Full PKCS#7 block");
    check(cbc_decrypt(encrypted, cbc_key, iv) == input, "CBC vector decryption with padding");
    for (std::size_t size : {0U, 1U, 15U, 16U, 17U, 31U, 32U, 4096U}) {
        Bytes bytes(size);
        for (std::size_t i = 0; i < size; ++i) bytes[i] = static_cast<std::uint8_t>(i % 128);
        check(cbc_decrypt(cbc_encrypt(bytes, key, iv), key, iv) == bytes, "CBC padding boundary " + std::to_string(size));
    }
    rejects([&] { cbc_decrypt({}, key, iv); }, "Empty ciphertext rejected");
    rejects([&] { cbc_decrypt(Bytes(17), key, iv); }, "Partial block rejected");
    Block bad_padding{};
    const Block raw = AES128(key).encrypt(bad_padding);
    rejects([&] { cbc_decrypt(Bytes(raw.begin(), raw.end()), key, zero); }, "Zero padding rejected");
    bad_padding.fill(2);
    bad_padding[14] = 3;
    const Block uneven = AES128(key).encrypt(bad_padding);
    rejects([&] { cbc_decrypt(Bytes(uneven.begin(), uneven.end()), key, zero); }, "Inconsistent padding rejected");
}

void encoding_tests() {
    check(pack({"", "a:b|c", " spaces "}) == "0:5:a:b|c8: spaces ", "Unambiguous ASCII encoding");
    check(unpack(pack({"", "a:b|c", " spaces "})) == Fields({"", "a:b|c", " spaces "}), "Field delimiters preserved");
    for (const auto& bad : {"", "a:x", "01:x", "2:x", "999999:x", "-1:x", ":x", "1:xy"}) {
        rejects([&] { unpack(bad); }, "Malformed fields rejected");
    }
    rejects([] { unpack(std::string("1:") + static_cast<char>(128)); }, "Non-ASCII frame rejected");
    rejects([] { pack(Fields(17, "x")); }, "Excessive fields rejected");
    rejects([] { pack({std::string(MAX_FRAME, 'x')}); }, "Oversized frame rejected");
    rejects([] { ascii_key("short"); }, "Short key rejected");
    rejects([] { ascii_key(std::string(17, 'x')); }, "Long key rejected");
    rejects([] { ascii_key(std::string(15, 'x') + '\n'); }, "Control key rejected");
    rejects([] { ascii_key(std::string(15, 'x') + static_cast<char>(128)); }, "Non-ASCII key rejected");
    check(ascii_key(" 12345678901234 ")[0] == ' ', "Key spaces preserved");
    rejects([] { unhex("0"); }, "Odd hex rejected");
    rejects([] { unhex("gg"); }, "Invalid hex rejected");
    check(hex(unhex("00aAFF")) == "00aaff", "Hex conversion");
    check(challenge_answer("0") == "18446744073709551615", "Challenge wrap modulo 2^64");
    rejects([] { challenge_answer("18446744073709551616"); }, "Nonce overflow rejected");
    rejects([] { challenge_answer("-1"); }, "Negative nonce rejected");
}

void handshake_tests() {
    const Block ka = ascii_key("AliceMasterKey16");
    const Block kb = ascii_key("BobMasterKey0016");
    const Block wrong = ascii_key("WrongMasterKey16");
    const std::string n1 = "123456789", n2 = "987654321";
    const Fields response = issue_session({"1", "Alice", "Bob", n1}, ka, kb);
    const Session alice = read_session(response, ka, n1);
    const Block bob = read_ticket({"3", alice.ticket}, kb);
    check(alice.key == bob, "Alice and Bob receive same session key");
    check(alice.ticket == response[2], "Bob ticket forwarded unchanged");
    const Session renewed = read_session(issue_session({"1", "Alice", "Bob", n1}, ka, kb), ka, n1);
    check(renewed.key != alice.key, "New KDC request generates a fresh session key");
    const Fields challenge = make_challenge(bob, n2);
    const Fields answer = answer_challenge(challenge, alice.key);
    check_answer(answer, bob, n2);
    check(true, "Five-step handshake");
    check(open(seal({"message", "1", "Hello Bob"}, alice.key), bob)[2] == "Hello Bob", "Session chat encryption");
    rejects([&] { read_session(response, ka, "111"); }, "N1 mismatch rejected");
    rejects([&] { read_session(response, wrong, n1); }, "Wrong Alice key rejected");
    rejects([&] { read_ticket({"3", alice.ticket}, wrong); }, "Wrong Bob key rejected");
    rejects([&] { check_answer(answer, bob, "222"); }, "Wrong N2 response rejected");
    rejects([&] { issue_session({"1", "Mallory", "Bob", n1}, ka, kb); }, "Unknown requester rejected");
    rejects([&] { issue_session({"1", "Alice", "Mallory", n1}, ka, kb); }, "Unknown recipient rejected");
    rejects([&] { read_session({"2", seal({"session", "SessionKey000016", "Alice", "Mallory", n1}, ka), alice.ticket}, ka, n1); }, "Response identity binding");
    rejects([&] { read_ticket({"3", seal({"ticket", "SessionKey000016", "Mallory"}, kb)}, kb); }, "Ticket identity binding");
    rejects([&] { answer_challenge({"CHAT", challenge[1]}, alice.key); }, "Out-of-order message rejected");
    rejects([&] { answer_challenge({"4", seal({"response", n2}, alice.key)}, alice.key); }, "Encrypted message type binding");
    rejects([&] { open("00:ff", ka); }, "Malformed envelope rejected");
    rejects([&] { open(std::string(32, 'z') + ':' + std::string(32, '0'), ka); }, "Malformed IV rejected");
    for (unsigned i = 0; i < 32; ++i) {
        const std::string generated = random_key();
        (void)ascii_key(generated);
        check(generated.size() == 16, "Generated session key meets ASCII contract");
    }
}
}

int main() {
    try {
        aes_vectors();
        encoding_tests();
        handshake_tests();
        std::cout << "PASS: " << checks << " checks (AES/CBC vectors, encoding, padding, KDC, challenge)\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "FAIL: " << error.what() << '\n';
        return 1;
    }
}

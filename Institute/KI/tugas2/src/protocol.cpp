#include "protocol.hpp"

#include <algorithm>
#include <charconv>
#include <limits>
#include <stdexcept>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <bcrypt.h>
#else
#include <fstream>
#endif

namespace ki {
namespace {
std::uint64_t number(const std::string& text) {
    std::uint64_t result = 0;
    if (text.empty() || (text.size() > 1 && text.front() == '0')) {
        throw std::runtime_error("Invalid unsigned integer");
    }
    const auto parsed = std::from_chars(text.data(), text.data() + text.size(), result);
    if (parsed.ec != std::errc{} || parsed.ptr != text.data() + text.size()) {
        throw std::runtime_error("Invalid unsigned integer");
    }
    return result;
}
}

void random_bytes(std::uint8_t* output, std::size_t size) {
#ifdef _WIN32
    if (size > std::numeric_limits<ULONG>::max() ||
        BCryptGenRandom(nullptr, output, static_cast<ULONG>(size), BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
        throw std::runtime_error("OS random generator failed");
    }
#else
    std::ifstream random("/dev/urandom", std::ios::binary);
    if (!random.read(reinterpret_cast<char*>(output), static_cast<std::streamsize>(size))) {
        throw std::runtime_error("OS random generator failed");
    }
#endif
}

Block random_block() {
    Block result{};
    random_bytes(result.data(), result.size());
    return result;
}

std::string random_key() {
    std::string result;
    while (result.size() < 16) {
        const Block bytes = random_block();
        for (const auto byte : bytes) {
            if (byte < 190 && result.size() < 16) result += static_cast<char>(32 + byte % 95);
        }
    }
    return result;
}

std::string nonce() {
    std::array<std::uint8_t, 8> bytes{};
    random_bytes(bytes.data(), bytes.size());
    std::uint64_t result = 0;
    for (const auto byte : bytes) result = (result << 8) | byte;
    return std::to_string(result);
}

std::string challenge_answer(const std::string& value) {
    return std::to_string(number(value) - std::uint64_t{1});
}

std::string pack(const Fields& fields) {
    if (fields.empty() || fields.size() > 16) throw std::runtime_error("Invalid field count");
    std::string result;
    for (const auto& field : fields) {
        if (!is_ascii(field)) throw std::runtime_error("Protocol accepts ASCII only");
        result += std::to_string(field.size()) + ':' + field;
        if (result.size() > MAX_FRAME) throw std::runtime_error("Frame too large");
    }
    return result;
}

Fields unpack(const std::string& data) {
    if (data.empty() || data.size() > MAX_FRAME || !is_ascii(data)) {
        throw std::runtime_error("Invalid ASCII frame");
    }
    Fields fields;
    std::size_t offset = 0;
    while (offset < data.size()) {
        const auto colon = data.find(':', offset);
        if (colon == std::string::npos || colon - offset > 5) throw std::runtime_error("Invalid field length");
        const auto size = number(data.substr(offset, colon - offset));
        offset = colon + 1;
        if (size > data.size() - offset || fields.size() >= 16) throw std::runtime_error("Truncated or excessive fields");
        fields.push_back(data.substr(offset, static_cast<std::size_t>(size)));
        offset += static_cast<std::size_t>(size);
    }
    return fields;
}

void require(const Fields& fields, std::size_t count, const std::string& type) {
    if (fields.size() != count || fields[0] != type) throw std::runtime_error("Unexpected protocol message");
}

std::string seal(const Fields& fields, const Block& key) {
    const std::string plaintext = pack(fields);
    const Block iv = random_block();
    return hex(iv) + ':' + hex(cbc_encrypt(Bytes(plaintext.begin(), plaintext.end()), key, iv));
}

Fields open(const std::string& envelope, const Block& key) {
    if (envelope.size() > MAX_FRAME || envelope.size() < 65 || envelope[32] != ':') {
        throw std::runtime_error("Invalid encrypted envelope");
    }
    const Bytes iv_bytes = unhex(envelope.substr(0, 32));
    Block iv{};
    std::copy(iv_bytes.begin(), iv_bytes.end(), iv.begin());
    const Bytes plaintext = cbc_decrypt(unhex(envelope.substr(33)), key, iv);
    return unpack(std::string(plaintext.begin(), plaintext.end()));
}

Fields issue_session(const Fields& request, const Block& alice_key, const Block& bob_key) {
    require(request, 4, "1");
    if (request[1] != "Alice" || request[2] != "Bob") throw std::runtime_error("Unknown identity");
    (void)number(request[3]);
    const std::string session_key = random_key();
    return {"2", seal({"session", session_key, "Alice", "Bob", request[3]}, alice_key),
                 seal({"ticket", session_key, "Alice"}, bob_key)};
}

Session read_session(const Fields& response, const Block& alice_key, const std::string& expected_nonce) {
    require(response, 3, "2");
    const Fields fields = open(response[1], alice_key);
    require(fields, 5, "session");
    if (fields[2] != "Alice" || fields[3] != "Bob" || fields[4] != expected_nonce) {
        throw std::runtime_error("KDC identity or nonce mismatch");
    }
    return {ascii_key(fields[1]), response[2]};
}

Block read_ticket(const Fields& request, const Block& bob_key) {
    require(request, 2, "3");
    const Fields fields = open(request[1], bob_key);
    require(fields, 3, "ticket");
    if (fields[2] != "Alice") throw std::runtime_error("Ticket identity mismatch");
    return ascii_key(fields[1]);
}

Fields make_challenge(const Block& key, const std::string& value) {
    (void)number(value);
    return {"4", seal({"challenge", value}, key)};
}

Fields answer_challenge(const Fields& request, const Block& key) {
    require(request, 2, "4");
    const Fields fields = open(request[1], key);
    require(fields, 2, "challenge");
    return {"5", seal({"response", challenge_answer(fields[1])}, key)};
}

void check_answer(const Fields& response, const Block& key, const std::string& expected_nonce) {
    require(response, 2, "5");
    const Fields fields = open(response[1], key);
    require(fields, 2, "response");
    if (fields[1] != challenge_answer(expected_nonce)) throw std::runtime_error("Challenge response mismatch");
}
}

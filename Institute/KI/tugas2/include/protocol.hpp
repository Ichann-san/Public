#pragma once

#include "aes.hpp"

#include <string>
#include <vector>

namespace ki {
constexpr std::size_t MAX_FRAME = 65536;
constexpr std::size_t MAX_MESSAGE = 4096;
using Fields = std::vector<std::string>;

void random_bytes(std::uint8_t* output, std::size_t size);
Block random_block();
std::string random_key();
std::string nonce();
std::string challenge_answer(const std::string& value);
std::string pack(const Fields& fields);
Fields unpack(const std::string& data);
void require(const Fields& fields, std::size_t count, const std::string& type);
std::string seal(const Fields& fields, const Block& key);
Fields open(const std::string& envelope, const Block& key);

struct Session {
    Block key{};
    std::string ticket;
};
Fields issue_session(const Fields& request, const Block& alice_key, const Block& bob_key);
Session read_session(const Fields& response, const Block& alice_key, const std::string& expected_nonce);
Block read_ticket(const Fields& request, const Block& bob_key);
Fields make_challenge(const Block& key, const std::string& value);
Fields answer_challenge(const Fields& request, const Block& key);
void check_answer(const Fields& response, const Block& key, const std::string& expected_nonce);
}

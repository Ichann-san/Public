CXX ?= g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -pthread -Iinclude
COMMON := src/aes.cpp src/protocol.cpp
HEADERS := $(wildcard include/*.hpp)

.PHONY: all test
all: build/ki_chat

build:
	mkdir -p build

build/ki_chat: $(COMMON) src/network.cpp src/main.cpp $(HEADERS) | build
	$(CXX) $(CXXFLAGS) $(COMMON) src/network.cpp src/main.cpp -o $@

build/unit_tests: $(COMMON) tests/unit.cpp $(HEADERS) | build
	$(CXX) $(CXXFLAGS) $(COMMON) tests/unit.cpp -o $@

test: build/ki_chat build/unit_tests
	./build/unit_tests
	python3 tests/integration.py --binary build/ki_chat

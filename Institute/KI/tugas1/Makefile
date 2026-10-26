CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2 -Iinclude
COMMON := src/des.cpp src/protocol.cpp

.PHONY: all test integration-test clean

all: server client

server: src/server.cpp $(COMMON) include/des.hpp include/protocol.hpp
	$(CXX) $(CXXFLAGS) src/server.cpp $(COMMON) -o $@

client: src/client.cpp $(COMMON) include/des.hpp include/protocol.hpp
	$(CXX) $(CXXFLAGS) src/client.cpp $(COMMON) -o $@

des_test: tests/des_test.cpp src/des.cpp include/des.hpp
	$(CXX) $(CXXFLAGS) tests/des_test.cpp src/des.cpp -o $@

test: des_test
	./des_test

integration-test: all
	bash tests/integration_test.sh

clean:
	rm -f server client des_test

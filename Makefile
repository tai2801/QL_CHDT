CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Isrc
SRC = src/main.cpp src/Phone.cpp src/Store.cpp src/Invoice.cpp src/utils.cpp
all: phone_store
phone_store: $(SRC)
	$(CXX) $(CXXFLAGS) -o phone_store $(SRC)
test: tests/test_store.cpp src/Phone.cpp src/Store.cpp src/Invoice.cpp src/utils.cpp
	$(CXX) $(CXXFLAGS) -o run_tests tests/test_store.cpp src/Phone.cpp src/Store.cpp src/Invoice.cpp src/utils.cpp
	./run_tests
clean:
	rm -f phone_store run_tests
.PHONY: all test clean

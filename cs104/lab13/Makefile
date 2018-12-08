CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

hashtablesTest: $(BIN_DIR) $(BIN_DIR)/hashtablesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/hashtablesTest

$(BIN_DIR)/hashtablesTest: $(BIN_DIR)/hashtablesTest.o $(BIN_DIR)/hashtables.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/hashtablesTest.o: $(TEST_DIR)/hashtablesTest.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

$(BIN_DIR)/hashtables.o: hashtables.cpp hashtables.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	rm -rf $(BIN_DIR)

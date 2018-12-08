CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR) $(BIN_DIR)/CheckBalancedParenthesesTest $(BIN_DIR)/CheckBalancedAllTest
	valgrind --leak-check=yes ./$(BIN_DIR)/CheckBalancedParenthesesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/CheckBalancedAllTest

$(BIN_DIR)/CheckBalancedParenthesesTest: $(BIN_DIR)/CheckBalancedParenthesesTest.o $(BIN_DIR)/CheckBalanced.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/CheckBalancedParenthesesTest.o: $(TEST_DIR)/CheckBalancedParenthesesTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/CheckBalancedAllTest: $(BIN_DIR)/CheckBalancedAllTest.o $(BIN_DIR)/CheckBalanced.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/CheckBalancedAllTest.o: $(TEST_DIR)/CheckBalancedAllTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/CheckBalanced.o: CheckBalanced.cpp CheckBalanced.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

CheckBalancedParenthesesTest: $(BIN_DIR) $(BIN_DIR)/CheckBalancedParenthesesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/CheckBalancedParenthesesTest

CheckBalancedAllTest: $(BIN_DIR) $(BIN_DIR)/CheckBalancedAllTest
	valgrind --leak-check=yes ./$(BIN_DIR)/CheckBalancedAllTest

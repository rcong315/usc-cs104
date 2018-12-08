CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

GraphTest: $(BIN_DIR) $(BIN_DIR)/GraphTest
	valgrind --leak-check=yes ./$(BIN_DIR)/GraphTest

$(BIN_DIR)/GraphTest: $(BIN_DIR)/GraphTest.o $(BIN_DIR)/graph.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/GraphTest.o: $(TEST_DIR)/GraphTest.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

$(BIN_DIR)/graph.o: graph.cpp graph.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	rm -rf $(BIN_DIR)

AllCombosTest: $(BIN_DIR) $(BIN_DIR)/GraphTest
	valgrind --leak-check=yes ./$(BIN_DIR)/GraphTest

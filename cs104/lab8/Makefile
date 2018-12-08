CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

test: $(BIN_DIR) $(BIN_DIR)/AllCombosTest
	valgrind --leak-check=yes ./$(BIN_DIR)/AllCombosTest

$(BIN_DIR)/AllCombosTest: $(BIN_DIR)/AllCombosTest.o $(BIN_DIR)/AllCombos.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/AllCombosTest.o: $(TEST_DIR)/AllCombosTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/AllCombos.o: AllCombos.cpp AllCombos.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

AllCombosTest: $(BIN_DIR) $(BIN_DIR)/AllCombosTest
	valgrind --leak-check=yes ./$(BIN_DIR)/AllCombosTest

CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all test tests: $(BIN_DIR) $(BIN_DIR)/PreOrderTest $(BIN_DIR)/InOrderTest $(BIN_DIR)/PostOrderTest $(BIN_DIR)/LevelOrderTest $(BIN_DIR)/SymmetricalTest
	./$(BIN_DIR)/PreOrderTest
	./$(BIN_DIR)/InOrderTest
	./$(BIN_DIR)/PostOrderTest
	./$(BIN_DIR)/LevelOrderTest
	./$(BIN_DIR)/SymmetricalTest

PreOrderTest: $(BIN_DIR) $(BIN_DIR)/PreOrderTest
	./$(BIN_DIR)/PreOrderTest

$(BIN_DIR)/PreOrderTest: $(TEST_DIR)/PreOrderTest.cpp $(BIN_DIR)/traversal.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

InOrderTest: $(BIN_DIR) $(BIN_DIR)/InOrderTest
	./$(BIN_DIR)/InOrderTest

$(BIN_DIR)/InOrderTest: $(TEST_DIR)/InOrderTest.cpp $(BIN_DIR)/traversal.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

PostOrderTest: $(BIN_DIR) $(BIN_DIR)/PostOrderTest
	./$(BIN_DIR)/PostOrderTest

$(BIN_DIR)/PostOrderTest: $(TEST_DIR)/PostOrderTest.cpp $(BIN_DIR)/traversal.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

LevelOrderTest: $(BIN_DIR) $(BIN_DIR)/LevelOrderTest
	./$(BIN_DIR)/LevelOrderTest

$(BIN_DIR)/LevelOrderTest: $(TEST_DIR)/LevelOrderTest.cpp $(BIN_DIR)/traversal.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

SymmetricalTest: $(BIN_DIR) $(BIN_DIR)/SymmetricalTest
	./$(BIN_DIR)/SymmetricalTest

$(BIN_DIR)/SymmetricalTest: $(TEST_DIR)/SymmetricalTest.cpp $(BIN_DIR)/traversal.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/traversal.o: traversal.cpp traversal.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	rm -rf $(BIN_DIR)

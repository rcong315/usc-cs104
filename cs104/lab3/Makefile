CC = g++
CPPFLAGS = -g -Wall -std=c++11
BIN_DIR = bin
TEST_DIR = tests
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR) $(BIN_DIR)/DestructorTest $(BIN_DIR)/InsertNthTest $(BIN_DIR)/RemoveDuplicatesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/DestructorTest
	valgrind --leak-check=yes ./$(BIN_DIR)/InsertNthTest
	valgrind --leak-check=yes ./$(BIN_DIR)/RemoveDuplicatesTest

$(BIN_DIR)/DestructorTest: $(BIN_DIR)/DestructorTest.o $(BIN_DIR)/LinkedList.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/DestructorTest.o: $(TEST_DIR)/DestructorTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/InsertNthTest: $(BIN_DIR)/InsertNthTest.o $(BIN_DIR)/LinkedList.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/InsertNthTest.o: $(TEST_DIR)/InsertNthTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/RemoveDuplicatesTest: $(BIN_DIR)/RemoveDuplicatesTest.o $(BIN_DIR)/LinkedList.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/RemoveDuplicatesTest.o: $(TEST_DIR)/RemoveDuplicatesTest.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/LinkedList.o: LinkedList.cpp LinkedList.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

$(TEST_DIR):
	mkdir $(TEST_DIR)

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

DestructorTest: $(BIN_DIR) $(BIN_DIR)/DestructorTest
	valgrind --leak-check=yes ./$(BIN_DIR)/DestructorTest

InsertNthTest: $(BIN_DIR) $(BIN_DIR)/InsertNthTest
	valgrind --leak-check=yes ./$(BIN_DIR)/InsertNthTest

RemoveDuplicatesTest: $(BIN_DIR) $(BIN_DIR)/RemoveDuplicatesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/RemoveDuplicatesTest

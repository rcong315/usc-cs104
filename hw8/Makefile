BIN_DIR = bin
CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: scrabble

scrabble: scrabble.cpp Move.o Board.o Bag.o ConsolePrinter.o Player.o Dictionary.o MaxLetterAI.o MaxScoreAI.o AIPlayer.o Trie.o
	$(CXX) $(CPPFLAGS) $^ -o $@
	
Tile.o: Tile.h 
	$(CXX) $(CPPFLAGS) -c $< -o $@

Square.o: Square.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Board.o: Board.cpp Board.h 
	$(CXX) $(CPPFLAGS) -c $< -o $@
	
Player.o: Player.cpp Player.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Bag.o: Bag.cpp Bag.h
	$(CXX) $(CPPFLAGS) -c $< -o $@
	
ConsolePrinter.o: ConsolePrinter.cpp ConsolePrinter.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Dictionary.o: Dictionary.cpp Dictionary.h 
	$(CXX) $(CPPFLAGS) -c $< -o $@

Move.o: Move.cpp Move.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Exceptions.o: Exceptions.h 
	$(CXX) $(CPPFLAGS) -c $< -o $@

rang.o: rang.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

MaxScoreAI.o: MaxScoreAI.cpp MaxScoreAI.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

MaxLetterAI.o: MaxLetterAI.cpp MaxLetterAI.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

AIPlayer.o: AIPlayer.cpp AIPlayer.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

Trie.o: Trie.cpp Trie.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o scrabble
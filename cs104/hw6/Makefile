BIN_DIR = bin
CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: search coloring

search: search.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

coloring: coloring.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@ 

.PHONY: clean
clean:
	rm -rf search coloring
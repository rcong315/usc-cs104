CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: cave

cave: cave.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf cave
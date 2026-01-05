CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g

.PHONY: all clean

all: backtracking dynamic

backtracking: backtracking.cpp
	$(CXX) $(CXXFLAGS) -o backtracking backtracking.cpp

dynamic: dynamic.cpp
	$(CXX) $(CXXFLAGS) -o dynamic dynamic.cpp

clean:
	rm -f backtracking dynamic

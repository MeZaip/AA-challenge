CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g

.PHONY: all clean

all: backtracking dynamic genetic

backtracking: backtracking.cpp
	$(CXX) $(CXXFLAGS) -o backtracking backtracking.cpp

dynamic: dynamic.cpp
	$(CXX) $(CXXFLAGS) -o dynamic dynamic.cpp

genetic: genetic.cpp
	$(CXX) $(CXXFLAGS) -o genetic genetic.cpp

positive: dynamic_positives.cpp
	$(CXX) $(CXXFLAGS) -o positive dynamic_positives.cpp

clean:
	rm -f backtracking dynamic genetic positive

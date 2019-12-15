CXX = g++
CXXFLAGS = -std=c++17 -Wall
VPATH = src
OBJ = $(patsubst src/%.cpp,obj/%.o,$(wildcard src/*.cpp))

all: dungeon

dungeon: $(OBJ)
	$(CXX) -o $@ $(OBJ)

obj/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm dungeon obj/*

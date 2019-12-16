CXX = g++
CXXFLAGS = -std=c++17 -Wall
VPATH = src
OBJ = $(patsubst src/%.cpp,obj/%.o,$(wildcard src/*.cpp))

all: dungeon

dungeon: $(OBJ)
	$(CXX) -o $@ $(OBJ)

obj/%.o: %.cpp obj
	$(CXX) $(CXXFLAGS) -c -o $@ $<

obj:
	mkdir $@

.PHONY: clean

clean:
	rm dungeon obj/*
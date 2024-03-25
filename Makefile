CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic -O2
LD = g++
LDFLAGS =

SRC=$(wildcard src/*.cpp)
HDR=$(wildcard src/*.h)
OBJ=$(patsubst src/%.cpp, %.o, $(SRC))

all: game doc
	:

compile: game
	:

fast:
	make -j16 compile

doc: Doxyfile $(SRC) $(HDR) README.md
	doxygen Doxyfile

game: $(OBJ)
	$(LD) $(LDFLAGS) $^ -o $@

run: game
	./game $(PATH_TO_CONFIG)

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include Makefile.d

Makefile.d: $(SRC) $(HDR)
	$(CXX) -MM $(SRC) > $@

clean:
	rm -rf game *.d *.o doc/

CC = gcc
CXXC = g++
OUTPUT = bin/Projeto01
WARNINGS = -Wall -Wextra -Wwrite-strings
LINKS = 
CFLAGS = -march=native -O2 -ftree-vectorize -fno-semantic-interposition -fno-plt -pipe -s -flto $(LINKS) $(WARNINGS)
DEBUG = -g

CSRC = $(wildcard src/*.c)
CXXSRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.c, obj/%.o, $(CSRC))
OBJ := $(OBJ) $(patsubst src/%.cpp, obj/%.o, $(CXXSRC))


$(OUTPUT): $(OBJ)
	$(CXXC) $^ -o $@ $(CFLAGS)

obj/%.o: src/%.c
	$(CC) $^ -c -o $@ $(CFLAGS)

obj/%.o: src/%.cpp
	$(CXXC) $^ -c -o $@ $(CFLAGS)

run: $(OUTPUT)
	bin/Projeto01


debug: bin/debug
bin/debug: src/*.cpp
	$(CXX) $^ -o $@ $(DEBUG)

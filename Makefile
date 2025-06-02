CPC = g++
CC = gcc
CFLAGS = -g -Iinclude 
LDFLAGS = -Llib -lglfw3dll lib/libglfw3dll.a

SRC = $(wildcard src/*.cpp) src/glad.c
BIN = bin

all:
	$(CPC) -o $(BIN)/bucket $(CFLAGS) $(SRC) $(LDFLAGS)
dirs:
	mkdir bin
run:all
	.\$(BIN)/bucket.exe

clean:
	rmdir $(BIN)


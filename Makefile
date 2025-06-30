CXX = g++
CC = gcc
CXXFLAGS = -g
CXXFLAGS += -Ilib/glfw/include -Ilib/glad/include
LDFLAGS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
BIN = bin

all:dirs libs program

libs:
	cd lib/glfw && cmake . && make
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c
dirs:
	mkdir -p ./$(BIN)
program:$(OBJ)
	$(CXX) -o $(BIN)/bucket $^ $(LDFLAGS)
%.o:%.c
	$(CXX) -o $@ -c $< $(CXXFLAGS)
run:all
	$(BIN)/bucket

clean:
	rm -rf $(BIN) $(OBJ)


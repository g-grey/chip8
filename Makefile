CXX = clang++
CXX_FLAGS = -std=c++11 -Wall
SDL_FLAGS = `sdl2-config --cflags --libs`

all: chip8

main.o: src/main.cpp
	${CXX} ${CXX_FLAGS} -o main.o -c src/main.cpp

chip8.o: src/chip8.cpp
	${CXX} ${CXX_FLAGS} -o chip8.o -c src/chip8.cpp

ui.o: src/ui.cpp
	${CXX} ${CXX_FLAGS} -o ui.o -c src/ui.cpp

debug.o: src/debug.cpp
	${CXX} ${CXX_FLAGS} -o debug.o -c src/debug.cpp

chip8: main.o chip8.o ui.o debug.o Makefile
	${CXX} -o chip8 ${SDL_FLAGS} chip8.o main.o ui.o debug.o

clean:
	rm -f ./*.o


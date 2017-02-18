

all:
		clang++ -std=c++1z -lSDL2 -I/usr/include/SDL2 -I./include src/*.cpp src/sdl/*.cpp


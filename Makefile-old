CXX=clang++
FLAGS=-std=c++1y -Wall -Wextra -Werror -pedantic-errors \
			-Wold-style-cast -Woverloaded-virtual -Wfloat-equal \
			-Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align \
			-Wconversion -Wshadow -Weffc++ -Wredundant-decls \
			-Winit-self -Wswitch-default -Wswitch-enum -Wundef \
			-Winline -Wunused -Wuninitialized
EXE=test_sdl2


all: debug

debug:
		$(CXX) $(FLAGS) -g -O0 -lSDL2 -I/usr/include/SDL2 -I./include src/*.cpp src/sdl/*.cpp -o $(EXE)

release:
		$(CXX) $(FLAGS) -DNDEBUG -O2 -lSDL2 -I/usr/include/SDL2 -I./include src/*.cpp src/sdl/*.cpp -o $(EXE)

clean:
		rm .*.swp

mrproper: clean
		rm $(EXE)

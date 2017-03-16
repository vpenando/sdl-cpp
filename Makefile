TARGET = sdltest
CXX = clang++-3.6
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)
CXXFLAGS = -std=c++14 -Wold-style-cast -Woverloaded-virtual -Wfloat-equal \
			-Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align \
			-Wconversion -Wshadow -Weffc++ -Wredundant-decls \
			-Winit-self -Wswitch-default -Wswitch-enum -Wundef \
			-Winline -Wunused -Wuninitialized
FLAGS_DEBUG = -D __SDL__ -O0 -g $(SDL_CFLAGS)
FLAGS_RELEASE = -D __SDL__ -O2 -DNDEBUG $(SDL_CFLAGS)
LDFLAGS = -lm $(SDL_LDFLAGS)

SOURCES=src/*.cpp src/sdl/*.cpp
INCLUDE=./include

all: debug

debug:
	$(CXX) -o $(TARGET) $(SOURCES) -I$(INCLUDE) $(CXXFLAGS) $(FLAGS_DEBUG) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LDFLAGS)
  
release:
	$(CXX) -o $(TARGET) $(SOURCES) -I$(INCLUDE) $(CXXFLAGS) $(FLAGS_RELEASE) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LDFLAGS)

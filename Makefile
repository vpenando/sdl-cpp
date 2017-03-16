TARGET = sdltest
CXX = clang++-3.6
CXXFLAGS = -std=c++14 -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align \
			-Wconversion -Wshadow -Weffc++ -Wredundant-decls  -Winit-self -Wswitch-default -Wswitch-enum -Wundef \
			-Winline -Wunused -Wuninitialized
			
FLAGS_DEBUG = -D __SDL__ -O0 -g $(SDL_CFLAGS)
FLAGS_RELEASE = -D __SDL__ -O2 -DNDEBUG $(SDL_CFLAGS)
LDFLAGS = -lm $(SDL_LDFLAGS)
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)

#SOURCES=src/*.cpp src/sdl/*.cpp
INCLUDE=./include
OBJ=main.o color.o event.o keyboard.o mouse.o point.o rect.o sdl_cpp.o surface.o window.o
all: debug

debug: $(OBJ) clean
	$(CXX) -o $(TARGET) $(OBJ) -I$(INCLUDE) $(CXXFLAGS) $(FLAGS_DEBUG) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LDFLAGS)
  
release: $(OBJ) clean
	$(CXX) -o $(TARGET) $(OBJ) -I$(INCLUDE) $(CXXFLAGS) $(FLAGS_RELEASE) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(LDFLAGS)

clean:
	rm $(TARGET)
	
%.o: src/sdl/%.cpp
	$(CXX) $(CXXFLAGS) $(FLAGS_DEBUG) $(SDL_CFLAGS) $(SDL_LDFLAGS) -c $<

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) $(FLAGS_DEBUG) $(SDL_CFLAGS) $(SDL_LDFLAGS) -c $<

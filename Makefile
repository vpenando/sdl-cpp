TARGET = sdltest
CXX = clang++-3.6
SDL_CFLAGS = $(shell sdl2-config --cflags)
SDL_LDFLAGS = $(shell sdl2-config --libs)
CXXFLAGS = -std=c++14 -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith \
			-Wconversion -Wshadow -Wredundant-decls -Winit-self -Wswitch-default -Wundef \
			-Winline -Wunused -Wuninitialized -D __SDL__ $(SDL_CFLAGS)
			
FLAGS_DEBUG = -O0 -g
FLAGS_RELEASE = -O2 -DNDEBUG

DEBUG=yes
ifeq ($(DEBUG),yes)
  CXXFLAGS += $(FLAGS_DEBUG)
else
  CXXFLAGS += $(FLAGS_RELEASE)
endif

LDFLAGS = -lm $(SDL_LDFLAGS)

#SOURCES=src/*.cpp src/sdl/*.cpp
INCLUDE=./include
OBJ=main.o color.o event.o keyboard.o mouse.o point.o rect.o sdl_cpp.o surface.o window.o

all: $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(CXXFLAGS) -I$(INCLUDE) $(SDL_CFLAGS) $(SDL_LDFLAGS)
  
clean:
	rm -rf *.o
	rm $(TARGET)
	
%.o: src/sdl/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $(SDL_CFLAGS) $(SDL_LDFLAGS) -c $<

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE) $(SDL_CFLAGS) $(SDL_LDFLAGS) -c $<

#include <iostream>

#include "sdl_cpp.h"
#include "window.h"

void foo(int*){
  std::cout << "lel";
}

void bar(SDL_Window*){
  std::cout << "bar";
}



int main(){
  sdl::Window window(SDL_CreateWindow(
    "An SDL2 window",                  // window title
    SDL_WINDOWPOS_UNDEFINED,           // initial x position
    SDL_WINDOWPOS_UNDEFINED,           // initial y position
    640,                               // width, in pixels
    480,                               // height, in pixels
    SDL_WINDOW_OPENGL                  // flags - see below
  ));
  bar(window);

}
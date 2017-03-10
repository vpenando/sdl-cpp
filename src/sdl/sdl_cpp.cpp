#include <sdl/sdl_cpp.h>
#include <stdexcept> // std::runtime_error

sdl::Context::Context(unsigned flags){
  if (SDL_Init(flags)){
    throw std::runtime_error{SDL_GetError()};
  }
}

sdl::Context::~Context(){
  SDL_Quit();
}
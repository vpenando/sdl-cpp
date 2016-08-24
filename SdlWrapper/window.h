#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <cstdint> // uint32_t
#include <string>  // std::string

#include <SDL.h>

#include "base.h"

namespace sdl{

  using BaseWindow = SDL_Base<SDL_Window, SDL_DestroyWindow>;

  // SDL_Window wrapper
  class Window : public BaseWindow{
  public:
    using flag_t = uint32_t;
    Window(value_type* ptr) : BaseWindow(ptr){}
  };
  
} // namespace sdl

#endif // __WINDOW_H__
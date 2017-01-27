#ifndef __MOUSE_H__
#define __MOUSE_H__

// **********************
// ** Standard library **
//***********************
// - 

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_GetMouseState

// **********************
// ** Custom lib files **
// **********************
#include "point.h" // sdl::Point

namespace sdl{
  namespace mouse{

    inline static::sdl::Point state() noexcept{
      ::sdl::Point point{};
      SDL_GetMouseState(&point.x, &point.y);
      return point;
    }

  }
} // namespace sdl::mouse

#endif // __MOUSE_H__
#ifndef __RECT_H__
#define __RECT_H__

#include <SDL.h> // SDL_Rect

#include "size.h"
#include "vector2.h"

namespace sdl{

  struct Rect final{
    Rect();
    Rect(int coordX, int coordY);
    Rect(int coordX, int coordY, unsigned width, unsigned height);
    operator SDL_Rect() const;
    Point pos;
    Size size;
  };

} // namespace sdl

#endif // __RECT_H__
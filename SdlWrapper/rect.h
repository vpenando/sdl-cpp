#ifndef __RECT_H__
#define __RECT_H__

#include "size.h"
#include "vector2.h"

namespace sdl{

  struct Rect final{
    Rect() : pos(0, 0), size(0, 0){}
    Rect(int coordX, int coordY) : Rect(coordX, coordY, 0, 0){}
    Rect(int coordX, int coordY, unsigned width, unsigned height) : pos(coordX, coordY), size(width, height){}
    Vector2i pos;
    Size size;
  };
} // namespace sdl

#endif // __RECT_H__
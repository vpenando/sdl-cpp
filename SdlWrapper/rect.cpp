#include "rect.h"

sdl::Rect::Rect()
  : pos(0, 0), size(0, 0)
{
}

sdl::Rect::Rect(int coordX, int coordY)
  : Rect(coordX, coordY, 0, 0)
{
}

sdl::Rect::Rect(int coordX, int coordY, unsigned width, unsigned height)
  : pos(coordX, coordY), size(width, height)
{
}

sdl::Rect::operator SDL_Rect() const{
  SDL_Rect rect;
  rect.x = pos.x;
  rect.y = pos.y;
  rect.w = size.w;
  rect.h = size.h;
  return rect;
}
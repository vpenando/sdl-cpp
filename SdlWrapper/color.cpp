#include "color.h"

sdl::Color::Color(u8 red, u8 green, u8 blue, u8 alpha) noexcept
  : r(red), g(green), b(blue), a(alpha)
{  
}

sdl::Color::operator SDL_Color() const noexcept{
  SDL_Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  return color;
}
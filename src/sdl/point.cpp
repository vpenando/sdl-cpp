#include <sdl/point.h>

sdl::Point::operator SDL_Point() const noexcept {
  SDL_Point point;
  point.x = x;
  point.y = y;
  return point;
}
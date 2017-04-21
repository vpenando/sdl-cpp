#ifndef __VECTOR2_H__
#define __VECTOR2_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Point

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/iconvertible.h> // sdl::api::IConvertible
#include <sdl/ecs/ecs.h>          // sdl::ecs::Component

namespace sdl{

  struct Point final :
    private SDL_Point,
    public api::IConvertible<SDL_Point>,
    public ecs::Component
  {
    Point() noexcept : Point(0, 0) {}
    Point(int p_x, int p_y) noexcept : SDL_Point(p_x, p_y) {}
    using SDL_Point::x;
    using SDL_Point::y;
    operator SDL_Point() const noexcept override;
  };

} // namespace sdl

inline bool operator==(sdl::Point const& p1, sdl::Point const& p2) noexcept{
  return p1.x == p2.x && p1.y == p2.y;
}

inline bool operator!=(sdl::Point const& p1, sdl::Point const& p2) noexcept{
  return !(p1 == p2);
}

#endif // __VECTOR2_H__

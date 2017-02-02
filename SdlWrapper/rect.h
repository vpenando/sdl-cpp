#ifndef __RECT_H__
#define __RECT_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Rect

// **********************
// ** Custom lib files **
// **********************
#include "ecs.h"          // sdl::ecs::Component
#include "iconvertible.h" // sdl::internal::IConvertible
#include "size.h"         // sdl::Size
#include "point.h"        // sdl::Point

namespace sdl{

  struct Rect final : public internal::IConvertible<SDL_Rect>, public ecs::Component{
    Rect() noexcept;
    Rect(int coordX, int coordY) noexcept;
		Rect(int coordX, int coordY, unsigned width, unsigned height) noexcept;
		Rect(SDL_Rect const& rect) noexcept;
    operator SDL_Rect() const noexcept override;
    //Point pos;
    //Size size;
		int x, y, w, h;
  };

} // namespace sdl

inline bool operator==(sdl::Rect const& r1, sdl::Rect const& r2) noexcept{
  return r1.x == r2.x && r1.y == r2.y && r1.w == r2.w && r1.h == r2.h;
}

inline bool operator!=(sdl::Rect const& r1, sdl::Rect const& r2) noexcept{
  return !(r1 == r2);
}

#endif // __RECT_H__
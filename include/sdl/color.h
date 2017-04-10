#ifndef __COLOR_H__
#define __COLOR_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Color, Uint8

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/iconvertible.h> // sdl::api::IConvertible
#include <sdl/ecs/ecs.h>          // sdl::ecs::Component
#include <sdl/types.h>            // sdl::u8, sdl::u32

namespace sdl{

  struct Color final : public api::IConvertible<SDL_Color>, public ecs::Component{
    Color(u8 red, u8 green, u8 blue, u8 alpha = 255) noexcept;
    Color(u32 val = 0) noexcept;
    operator SDL_Color() const noexcept override;
    u8 r, g, b, a;
    const static Color BLACK;
    const static Color RED;
    const static Color GREEN;
    const static Color BLUE;
  };

} // namespace sdl

inline bool operator==(sdl::Color const& c1, sdl::Color const& c2) noexcept{
  return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

inline bool operator!=(sdl::Color const& c1, sdl::Color const& c2) noexcept{
  return !(c1 == c2);
}

#endif // __COLOR_H__

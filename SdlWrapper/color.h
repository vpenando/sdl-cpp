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
#include "ecs.h"          // sdl::ecs::Component
#include "iconvertible.h" // sdl::internal::IConvertible

namespace sdl{
  
  using u8 = Uint8;
  using u16 = Uint16;
  using u32 = Uint32;
  
  struct Color final : public internal::IConvertible<SDL_Color>, public ecs::Component{
    Color(u8 red, u8 green, u8 blue, u8 alpha = 255) noexcept;
    Color(u32 val) noexcept;
    operator SDL_Color() const noexcept override;
    u8 r, g, b, a;
    const static Color BLACK;
    const static Color RED;
    const static Color GREEN;
    const static Color BLUE;
  };

} // namespace sdl

#endif // __COLOR_H__
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
#include "iconvertible.h" // sdl::internal::IConvertible

namespace sdl{
  
  using u8 = Uint8;
  
  struct Color final : public internal::IConvertible<SDL_Color>{
    Color(u8 red, u8 green, u8 blue, u8 alpha = 0) noexcept;
    operator SDL_Color() const noexcept override;
    u8 r, g, b, a;
  };

} // namespace sdl

#endif // __COLOR_H__
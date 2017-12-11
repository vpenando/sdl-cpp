#include <sdl/color.h>

const sdl::Color sdl::Color::BLACK = 0x00000000;
const sdl::Color sdl::Color::RED   = 0xff0000ff;
const sdl::Color sdl::Color::GREEN = 0x00ff00ff;
const sdl::Color sdl::Color::BLUE  = 0x0000ffff;

//! @brief Ctor
//! @param red   The R value
//! @param green The G value
//! @param blue  The B value
//! @param alpha The A value
sdl::Color::Color(u8 red, u8 green, u8 blue, u8 alpha) noexcept
  : r(red), g(green), b(blue), a(alpha){}

//! @brief Ctor
//! @param val The hexadecimal representation of a color
sdl::Color::Color(u32 val) noexcept : Color(
  val >> 24 & 0xff,
  val >> 16 & 0xff,
  val >> 8 & 0xff,
  val & 0xff){}

sdl::Color::operator SDL_Color() const noexcept{
  SDL_Color color;
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;
  return color;
}
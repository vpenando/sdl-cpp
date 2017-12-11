#include <sdl/rect.h>

//! @brief Default ctor
sdl::Rect::Rect() noexcept
  : x(0), y(0), w(0), h(0)
{
}

//! @brief Ctor
//! @param width   The rectangle width
//! @param height  The rectangle height
sdl::Rect::Rect(unsigned width, unsigned height) noexcept
  : Rect(0, 0, width, height)
{
}

//! @brief Ctor
//! @param coord_x The X coordinate
//! @param coord_y The Y coordinate
//! @param width   The rectangle width
//! @param height  The rectangle height
sdl::Rect::Rect(int coord_x, int coord_y, unsigned width, unsigned height) noexcept
  : x(coord_x), y(coord_y), w(width), h(height)
{
}

//! @brief Ctor
//! @param rect A SDL_Rect
sdl::Rect::Rect(SDL_Rect const& rect) noexcept
  : Rect(rect.x, rect.y, static_cast<unsigned>(rect.w), static_cast<unsigned>(rect.h))
{
}

sdl::Rect::operator SDL_Rect() const noexcept {
  SDL_Rect rect;
  rect.x = x;
  rect.y = y;
  rect.w = static_cast<int>(w);
  rect.h = static_cast<int>(h);
  return rect;
}

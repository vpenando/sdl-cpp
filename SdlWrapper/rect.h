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
#include "iconvertible.h" // sdl::internal::IConvertible
#include "size.h"         // sdl::Size
#include "point.h"        // sdl::Point

namespace sdl{

  struct Rect final : public internal::IConvertible<SDL_Rect>{
    Rect();
    Rect(int coordX, int coordY);
    Rect(int coordX, int coordY, unsigned width, unsigned height);
    operator SDL_Rect() const override;
    Point pos;
    Size size;
  };

} // namespace sdl

#endif // __RECT_H__
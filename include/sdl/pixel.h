#ifndef __PIXEL_H__
#define __PIXEL_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/matrix.h> // sdl::api::Matrix
#include <sdl/color.h>      // sdl::Color
#include <sdl/surface.h>    // sdl::Surface

namespace sdl {
  
  using Pixel = Color;
  using PixelMatrix = api::Matrix<Pixel>;

  Pixel pixel_at(sdl::Surface const& surface, unsigned x, unsigned y);
  PixelMatrix pixels(sdl::Surface const& surface);

} // namespace sdl

#endif // __PIXEL_H__
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

//! @namespace sdl
//! @brief The SDL wrapper main namespace
namespace sdl {
  
  //! @typedef Pixel
  //! @brief   An alias of Color
  //! @see     Color
  using Pixel = Color;
  //! @typedef PixelMatrix
  //! @brief   An alias of Matrix
  //! @see     Matrix
  using PixelMatrix = api::Matrix<Pixel>;

  //! @brief Returns the pixel at (X, Y) in an image
  //! @param surface The image we work on
  //! @param x       The X coordinate
  //! @param y       The Y coordinate
  //! @pre   surface must be valid
  //! @pre   x < surface width
  //! @pre   y < surface height
  //! @returns The pixel as a RGBA color
  Pixel pixel_at(sdl::Surface const& surface, unsigned x, unsigned y);
  
  //! @brief Returns the pixels of a given image
  //! @param surface The image we work on
  //! @return The pixels as a PixelMatrix
  PixelMatrix pixels(sdl::Surface const& surface);

} // namespace sdl

#endif // __PIXEL_H__

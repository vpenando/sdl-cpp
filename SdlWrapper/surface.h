#ifndef __SURFACE_H__
#define __SURFACE_H__

// **********************
// ** Standard library **
//***********************
#include <string> // std::string

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Surface, SDL_FreeSurface

// **********************
// ** Custom lib files **
// **********************
#include "base.h" // sdl::internal::memory::Base
#include "ecs.h"  // sdl::internal::Component
#include "size.h" // sdl::Size

namespace sdl{
  namespace internal{
    using BaseSurface = Base<SDL_Surface, SDL_FreeSurface>;
  } // namespace sdl::internal

  class Surface final : public internal::BaseSurface{
  public:
    Surface::Surface(SDL_Surface *ptr);
    Size size() const noexcept;

  private:
    Size size_;
  };

  SDL_Surface *load_bmp(std::string const& path);

} // namespace sdl

#endif // __SURFACE_H__
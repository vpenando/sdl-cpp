#ifndef __SURFACE_H__
#define __SURFACE_H__

#include <SDL.h>  // SDL_Window, SDL_DestroyWindow

#include "base.h" // memory::Base
#include "size.h" // Size

namespace sdl{
  namespace internal{
    using BaseSurface = Base<SDL_Surface, SDL_FreeSurface>;
  } // namespace sdl::internal

  class Surface final : public internal::BaseSurface{
  public:
    explicit Surface::Surface(SDL_Surface *ptr);
    Size size() const noexcept;

  private:
    Size size_;
  };

} // namespace sdl

#endif // __SURFACE_H__
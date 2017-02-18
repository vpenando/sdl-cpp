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
#include <sdl/ecs/ecs.h>            // sdl::api::Component
#include <sdl/size.h>               // sdl::Size
#include <sdl/api/memory/wrapper.h> // sdl::api::memory::Wrapper

namespace sdl{
  namespace api{
    using BaseSurface = memory::Wrapper<SDL_Surface, SDL_FreeSurface>;
  } // namespace sdl::api

  class Surface final : public api::BaseSurface{
  public:
    Surface(SDL_Surface *ptr);
    Size size() const noexcept;

  private:
    Size size_;
  };

  SDL_Surface *load_bmp(std::string const& path);

} // namespace sdl

#endif // __SURFACE_H__

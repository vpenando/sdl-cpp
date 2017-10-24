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
#include <sdl/exception.h>          // sdl::Exception
#include <sdl/size.h>               // sdl::Size
#include <sdl/api/memory/wrapper.h> // sdl::api::memory::Wrapper

namespace sdl {

  class Surface final {
  public:
    explicit Surface(SDL_Surface *ptr);
    Surface(Surface const& surface);
    ~Surface();
    Surface& operator=(Surface const& surface);
    Size size() const noexcept;
    operator SDL_Surface*() const noexcept;
  private:
    void copy_surface(Surface const& surface);
    SDL_Surface *ptr_;
  };

  template<class Function, class ...Args>
  Surface make_surface(Function f, Args... args) {
    auto ptr = f(args...);
    if (!ptr) {
      throw sdl::LoadingError{SDL_GetError()};
    }
    return Surface(ptr);
  }
  
  inline Surface load_bmp(std::string const& filename) {
    return make_surface([&](auto const& f) { return SDL_LoadBMP(f.c_str()); }, filename);
  }

} // namespace sdl

#endif // __SURFACE_H__

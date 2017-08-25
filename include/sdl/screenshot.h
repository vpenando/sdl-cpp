#ifndef __SCREENSHOT_H__
#define __SCREENSHOT_H__

#include <cassert> // assert

#include <SDL.h>
#include <sdl/surface.h> // sdl::Surface
#include <sdl/window.h>  // sdl::Window

namespace sdl {

  Surface to_surface(SDL_Window *window) {
    assert(window && "Null window");
    return make_surface(SDL_GetWindowSurface, window);
  }
  
  void save_bmp(Surface const& surface, std::string const& filename) {
    if (SDL_SaveBMP(surface, filename.c_str()) {
      throw std::runtime_error{SDL_GetError()};
    }  
  }
  
  void take_screenshot(SDL_Window *window, std::string const& filename) {
    assert(window && "Null window");
    save_bmp(to_surface(window), filename);
  }

} // namespace sdl

#endif // __SCREENSHOT_H__

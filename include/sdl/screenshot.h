#ifndef __SCREENSHOT_H__
#define __SCREENSHOT_H__

#include <cassert> // assert

#include <SDL.h>
#include <sdl/surface.h> // sdl::Surface
#include <sdl/window.h>  // sdl::Window

namespace sdl {

  Surface to_surface(SDL_Window *window);
  void save_bmp(Surface const& surface, std::string const& filename);
  void take_screenshot(sdl::Window const& window, std::string const& filename);

} // namespace sdl

#endif // __SCREENSHOT_H__

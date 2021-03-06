#include <sdl/screenshot.h>

sdl::Surface to_surface(SDL_Window *window) {
  assert(window && "Null window");
  return sdl::make_surface(SDL_GetWindowSurface, window);
}

void sdl::save_bmp(sdl::Surface const& surface, std::string const& filename) {
  if (SDL_SaveBMP(surface, filename.c_str())) {
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::take_screenshot(sdl::Window const& window, std::string const& filename) {
  assert(window && "Null window");
  save_bmp(to_surface(window), filename);
}
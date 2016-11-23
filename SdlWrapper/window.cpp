#include "window.h"

#include <stdexcept> // std::runtime_error

sdl::Window::Window(std::string const& name, Size const& size, flag_t flags)
  : Window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.w, size.h, flags), renderer::ACCELERATED){
}

sdl::Window::Window(SDL_Window *window, int renderer_flags)
  : internal::BaseWindow(window), renderer_(SDL_CreateRenderer(*this, -1, renderer_flags))
{
  // Window ptr is checked in Wrapper::Wrapper
  // Renderer ptr is checked in Wrapper::Wrapper
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  assert(w > 0 && "Invalid window width");
  assert(h > 0 && "Invalid window height");
  size_.w = static_cast<unsigned>(w);
  size_.h = static_cast<unsigned>(h);
}

sdl::Size sdl::Window::size() const noexcept{
  return size_;
}

void sdl::Window::blit(Surface const& surface, Point const& coords, NullableRect const& src_rect){
  const Texture texture{SDL_CreateTextureFromSurface(renderer_, surface)};
  const auto size = surface.size();
  const SDL_Rect src = (src_rect) ? src_rect.value() : Rect{0, 0, size.w, size.h};
  const SDL_Rect dest = {coords.x, coords.y, src.w, src.h};
  const auto ret = SDL_RenderCopy(renderer_, texture, &src, &dest);
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::Window::blit(internal::IDrawable const& drawable, Point const& coords, NullableRect const& src_rect){
  drawable.on_window(*this, coords, src_rect);
}

void sdl::Window::update(){
  SDL_RenderPresent(renderer_);
  SDL_RenderClear(renderer_);
}
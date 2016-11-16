#include "window.h"

#include <stdexcept> // std::runtime_error

sdl::Window::Window(std::string const& name, Size const& size, flag_t flags, Point const& pos, int renderer_flags)
  : Window(SDL_CreateWindow(name.c_str(), pos.x, pos.y, size.w, size.h, flags), size, renderer_flags){}

sdl::Window::Window(SDL_Window *window, Size const& size, int renderer_flags)
  : internal::BaseWindow(window), size_(size),
  renderer_(SDL_CreateRenderer(*this, -1, renderer_flags))
{
  assert(size.w > 0 && "Invalid window width 0");
  assert(size.h > 0 && "Invalid window height 0");
}

sdl::Size sdl::Window::size() const noexcept{
  return size_;
}

void sdl::Window::blit(Surface const& surface, Point const& coords, NullableRect const& src_rect){
  assert(surface && "Invalid SDL surface");
  const Texture texture{SDL_CreateTextureFromSurface(renderer_, surface)};
  const auto size = surface.size();
  const auto src  = (src_rect) ? src_rect.value() : SDL_Rect{0, 0, static_cast<int>(size.w), static_cast<int>(size.h)};
  const auto dest = SDL_Rect{coords.x, coords.y, src.w, src.h};
  const auto ret  = SDL_RenderCopy(renderer_, texture, &src, &dest);
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::Window::update(){
  SDL_RenderPresent(renderer_);
}
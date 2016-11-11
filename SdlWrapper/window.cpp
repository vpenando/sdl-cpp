#include "window.h"

#include <stdexcept> // std::runtime_error

sdl::Window::Window(std::string const& name, Size const& size, flag_t flags, Vector2i const& pos, SDL_RendererFlags renderer_flags)
  : Window(SDL_CreateWindow(name.c_str(), pos.x, pos.y, size.w, size.h, flags), size, renderer_flags)
{
}

sdl::Window::Window(SDL_Window *window, Size const& size, SDL_RendererFlags renderer_flags)
  : internal::BaseWindow(window), size_(size),
    renderer_(SDL_CreateRenderer(*this, -1, renderer_flags)),
    screen_(SDL_GetWindowSurface(*this))
{
}

sdl::Size sdl::Window::size() const noexcept{
  return size_;
}

void sdl::Window::blit(Surface const& surface, Rect const& img_rect, NullableRect const& opt_rect){
  assert(surface && "Invalid SDL surface");
  SDL_Rect dst_rect;
  SDL_Rect *rect_ptr = NULL; // No need to delete: stores a local variable address
  if(opt_rect){
    dst_rect = opt_rect.value();
    rect_ptr = &dst_rect;
  }
  const SDL_Rect source_rect = img_rect;
  const auto ret = SDL_BlitSurface(surface, &source_rect, screen_, rect_ptr);
  if(ret != 0){
    throw std::runtime_error{"Error: SDL_BlitSurface failed with error code " + std::to_string(ret)};
  }
}

void sdl::Window::update(){
  const auto ret = SDL_UpdateWindowSurface(*this);
  if(ret != 0){
    throw std::runtime_error{"Error: SDL_UpdateWindowSurface failed with error code " + std::to_string(ret)};
  }
}
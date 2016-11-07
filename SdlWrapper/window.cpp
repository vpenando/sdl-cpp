#include "window.h"

#include <stdexcept> // std::runtime_error
#include <filesystem>

sdl::Window::Window(std::string const& name, Size const& size, flag_t flags, Vector2i const& pos, SDL_RendererFlags renderer_flags)
  : internal::BaseWindow(SDL_CreateWindow(name.c_str(), pos.x, pos.y, size.w, size.h, flags)), size_(size),
    renderer_(SDL_CreateRenderer(*this, -1, renderer_flags)),
    screen_(SDL_GetWindowSurface(*this))
{
}

sdl::Window::Window(SDL_Window *window, SDL_RendererFlags renderer_flags)
  : internal::BaseWindow(window), size_(),
    renderer_(SDL_CreateRenderer(*this, -1, renderer_flags)),
    screen_(SDL_GetWindowSurface(*this))
{
}

sdl::Size sdl::Window::size() const noexcept{
  return size_;
}

void sdl::Window::blit(Surface const& surface, Vector2i const& pos, NullableRect const& opt_rect){
  assert(surface && "Invalid SDL surface");
  SDL_Rect source_rect;
  source_rect.x = pos.x;
  source_rect.y = pos.y;
  source_rect.w = surface.size().w;
  source_rect.h = surface.size().h;
  SDL_Rect dstrect;
  SDL_Rect *rect_ptr = NULL; // No need to delete: stores a local variable address
  if(opt_rect){
    const auto rect = opt_rect.value();
    dstrect.x = rect.pos.x;
    dstrect.y = rect.pos.y;
    dstrect.w = static_cast<int>(rect.size.w);
    dstrect.h = static_cast<int>(rect.size.h);
    rect_ptr = &dstrect;
  }
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
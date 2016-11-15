#include "window.h"

#include <stdexcept> // std::runtime_error

sdl::Window::Window(std::string const& name, Size const& size, flag_t flags, Point const& pos, SDL_RendererFlags renderer_flags)
  : Window(SDL_CreateWindow(name.c_str(), pos.x, pos.y, size.w, size.h, flags), size, renderer_flags){}

sdl::Window::Window(SDL_Window *window, Size const& size, SDL_RendererFlags renderer_flags)
  : internal::BaseWindow(window), size_(size),
  renderer_(SDL_CreateRenderer(*this, -1, renderer_flags)),
  screen_(SDL_GetWindowSurface(*this)){
  assert(size.w > 0 && "Invalid window width 0");
  assert(size.h > 0 && "Invalid window height 0");
}

sdl::Size sdl::Window::size() const noexcept{
  return size_;
}

namespace{
  template<class T>
  using NullableSdlType = typename sdl::internal::Nullable<T>::value_type::value_type;

  template<class T>
  using NullableSdlTypePtr = std::unique_ptr<NullableSdlType<T>>;

  template<class T>
  NullableSdlTypePtr<T> ptr_from_nullable(sdl::internal::Nullable<T> const& nullable){
    return (nullable) ? std::make_unique<NullableSdlType<T>>(nullable.value()) : NULL;
  }
} // namespace


void sdl::Window::blit(Surface const& surface, Rect const& img_rect, NullableRect const& opt_rect){
  assert(surface && "Invalid SDL surface");
  assert(screen_ && "Invalid SDL screen");
  const SDL_Rect rect = img_rect;
  auto opt_rect_ptr = ptr_from_nullable(opt_rect);
  const auto ret = SDL_BlitSurface(surface, &rect, screen_, opt_rect_ptr.get());
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::Window::update(){
  const auto ret = SDL_UpdateWindowSurface(*this);
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}
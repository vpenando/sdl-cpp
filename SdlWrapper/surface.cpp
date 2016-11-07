#include "surface.h"
#include <stdexcept>

sdl::Surface::Surface(SDL_Surface *ptr) : internal::BaseSurface(ptr){
  if(!ptr){
    throw std::runtime_error{"Cannot load SDL surface"};
  }
  size_ = Size{static_cast<unsigned>(ptr->w), static_cast<unsigned>(ptr->h)};
}

sdl::Size sdl::Surface::size() const noexcept{
  return size_;
}
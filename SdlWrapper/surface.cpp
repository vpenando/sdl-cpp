#include "surface.h"

sdl::Surface::Surface(SDL_Surface *ptr) : internal::BaseSurface(ptr){
  // Ptr is checked in Wrapper::Wrapper
  const auto width  = ptr->w;
  const auto height = ptr->h;
  assert(width  >= 0 && "Surface width must be superior than 0");
  assert(height >= 0 && "Surface height must be superior than 0");
  size_ = Size{static_cast<unsigned>(width), static_cast<unsigned>(height)};
}

sdl::Size sdl::Surface::size() const noexcept{
  return size_;
}
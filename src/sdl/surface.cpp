#include <sdl/surface.h>

#include <algorithm> // std::swap
#include <stdexcept> // std::runtime_error

enum Mask : Uint32 {
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  R = 0xff000000,
  G = 0x00ff0000,
  B = 0x0000ff00,
  A = 0x000000ff
#else
  R = 0x000000ff,
  G = 0x0000ff00,
  B = 0x00ff0000,
  A = 0xff000000
#endif
};

sdl::Surface::Surface(SDL_Surface *ptr) : ptr_(ptr) /*api::BaseSurface(ptr)*/{
  assert(ptr && "Null pointer");
}

sdl::Surface::Surface(Surface const& surface) {
  copy_surface(surface);
}

sdl::Surface::~Surface() {
  if (ptr_) {
    SDL_FreeSurface(ptr_);
  }
}

sdl::Surface& sdl::Surface::operator=(Surface const& surface) {
  auto copy(surface);
  std::swap(this->ptr_, copy.ptr_);
  return *this;
}

sdl::Size sdl::Surface::size() const noexcept{
  const auto width  = ptr_->w;
  const auto height = ptr_->h;
  assert(width  >= 0 && "Surface width must be superior than 0");
  assert(height >= 0 && "Surface height must be superior than 0");
  return Size{static_cast<unsigned>(width), static_cast<unsigned>(height)};
}

sdl::Surface::operator SDL_Surface*() const noexcept {
  assert(ptr_ && "Null pointer");
  return ptr_;
}

void sdl::Surface::copy_surface(Surface const& surface) {
  assert(surface.ptr_ && "Null pointer");
  assert(surface.ptr_->format && "Null pointer");
  ptr_ = SDL_CreateRGBSurface(0, surface.ptr_->w,
    surface.ptr_->h, surface.ptr_->format->BitsPerPixel, Mask::R, Mask::G, Mask::B, Mask::A);
  if (!ptr_) {
    throw sdl::LoadingError{"Cannot create surface"};
  }
  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = surface.ptr_->w;
  rect.h = surface.ptr_->h;
  const auto ret = SDL_BlitSurface(surface.ptr_, &rect, ptr_, 0);
  if (ret != 0) {
    throw sdl::LoadingError{SDL_GetError()};
  }
}

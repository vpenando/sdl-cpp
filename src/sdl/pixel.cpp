#include <sdl/pixel.h>

#include <cassert> // assert

constexpr auto IS_BIG_ENDIAN = SDL_BYTEORDER == SDL_BIG_ENDIAN;

inline sdl::u32 pixel_from_endian(sdl::u8 *ptr) {
  assert(ptr && "Null pointer");
#if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
  return p[0] << 16 | p[1] << 8 | p[2];
#else
  return ptr[0] | ptr[1] << 8 | ptr[2] << 16;
#endif
}

sdl::u32 get_pixel(SDL_Surface *surface, int x, int y) {
  assert(surface && "Null pointer");
  assert(surface->format && "Null pointer");
  assert(surface->pixels && "Null pointer");
  int bpp = surface->format->BytesPerPixel;
  /* Here p is the address to the pixel we want to retrieve */
  auto p = static_cast<sdl::u8 *>(surface->pixels) + y * surface->pitch + x * bpp;
  assert(p && "Invalid pixel address");
  switch (bpp) {
  case 1: return *p;
  case 2: return *reinterpret_cast<sdl::u16 *>(p);
  case 3: return pixel_from_endian(p);
  case 4: return *reinterpret_cast<sdl::u32 *>(p);
  default:
    throw std::runtime_error{"Unknown image bytes per pixel"};
  }
}

sdl::Pixel sdl::pixel_at(sdl::Surface const& surface, unsigned x, unsigned y) {
  const auto surface_size = surface.size();
  assert(x < surface_size.w && "Out of bounds");
  assert(y < surface_size.h && "Out of bounds");
  SDL_Surface *surface_ptr = surface;
  assert(surface_ptr && "Null pointer");
  const auto raw_pixel = get_pixel(surface_ptr, static_cast<int>(x), static_cast<int>(y));
  Pixel pixel;
  assert(surface_ptr->format && "Null surface format");
  SDL_GetRGBA(raw_pixel, surface_ptr->format, &pixel.r, &pixel.g, &pixel.b, &pixel.a);
  return pixel;
}

sdl::PixelMatrix sdl::pixels(sdl::Surface const& surface) {
  const auto surface_size = surface.size();
  sdl::PixelMatrix mat{surface_size.w, surface_size.h};
  for (unsigned i{}; i < surface_size.w; i++) {
    for (unsigned j{}; j < surface_size.h; j++) {
      mat(i, j) = pixel_at(surface, i, j);
    }
  }
  return mat;
}
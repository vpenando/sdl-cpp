#include <sdl/window.h>
#include <sdl/exception.h>

#include <algorithm> // std::copy
#include <stdexcept> // std::runtime_error

namespace api = sdl::api;

sdl::Window::Window(std::string const& name, Size const& size, flag_t flags)
  : Window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    static_cast<int>(size.w), static_cast<int>(size.h), flags), renderer::ACCELERATED){}

sdl::Window::Window(std::string const& name, Point const& coords, Size const& size, flag_t flags)
  : Window(SDL_CreateWindow(name.c_str(), coords.x, coords.y,
    static_cast<int>(size.w), static_cast<int>(size.h), flags), renderer::ACCELERATED){}

sdl::Window::Window(std::string const& name, Rect const& rect, flag_t flags)
  : Window(SDL_CreateWindow(name.c_str(), rect.x, rect.y,
    static_cast<int>(rect.w), static_cast<int>(rect.h), flags), renderer::ACCELERATED){}

sdl::Window::Window(SDL_Window *window, unsigned renderer_flags)
  : api::BaseWindow(window), renderer_(SDL_CreateRenderer(*this, -1, renderer_flags)) {
  // Window ptr is checked in Wrapper::Wrapper
  // Renderer ptr is checked in Wrapper::Wrapper
  int w, h;
  SDL_GetWindowSize(window, &w, &h);
  assert(w > 0 && "Invalid window width");
  assert(h > 0 && "Invalid window height");
  size_.w = static_cast<unsigned>(w);
  size_.h = static_cast<unsigned>(h);
}

sdl::Size sdl::Window::size() const noexcept {
  return size_;
}

void sdl::Window::blit(Surface const& surface, Point const& coords, NullableRect const& src_rect) {
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  const Texture texture{SDL_CreateTextureFromSurface(renderer_, surface)};
  blit(texture, coords, src_rect);
  /*const auto size = surface.size();
  const SDL_Rect src = (src_rect) ? src_rect.value() : Rect{0, 0, size.w, size.h};
  const SDL_Rect dest = {coords.x, coords.y, src.w, src.h};
  const auto ret = SDL_RenderCopy(renderer_, texture, &src, &dest);
  if(ret != 0){
  throw std::runtime_error{SDL_GetError()};
  }*/
}

void sdl::Window::blit(Texture const& texture, Point const& coords, NullableRect const& src_rect) {
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  assert(w > 0 && "Invalid texture width");
  assert(h > 0 && "Invalid texture height");
  const SDL_Rect src = (src_rect) ? src_rect.value() : Rect{0, 0, static_cast<unsigned>(w), static_cast<unsigned>(h)};
  const SDL_Rect dest = {coords.x, coords.y, src.w, src.h};
  const auto ret = SDL_RenderCopy(renderer_, texture, &src, &dest);
  if (ret != 0) {
    throw sdl::RenderingError{SDL_GetError()};
  }
}

void sdl::Window::blit(IDrawable const& drawable, Point const& coords, NullableRect const& src_rect) {
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  drawable.on_window(*this, coords, src_rect);
}

void sdl::Window::draw_point(sdl::Point const& point, NullableColor const& color) {
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  Color renderer_color{};
  if (color) {
    renderer_color = get_renderer_color();
    set_renderer_color(color.value());
  }
  const auto ret = SDL_RenderDrawPoint(renderer_, point.x, point.y);
  if (color) {
    set_renderer_color(renderer_color);
  }
  if (ret != 0) {
    throw sdl::RenderingError{SDL_GetError()};
  }
}

void sdl::Window::draw_points(std::vector<sdl::Point> const& points, NullableColor const& color) {
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  const auto size = points.size();
  std::vector<SDL_Point> raw_points(size);
  std::copy(points.begin(), points.end(), raw_points.begin());
  Color renderer_color{};
  if (color) {
    renderer_color = get_renderer_color();
    set_renderer_color(color.value());
  }
  const auto ret = SDL_RenderDrawPoints(renderer_, raw_points.data(), static_cast<int>(raw_points.size()));
  if (ret != 0) {
    throw sdl::RenderingError{SDL_GetError()};
  }
  if (color) {
    set_renderer_color(renderer_color);
  }
}

void sdl::Window::draw_line(sdl::Point const& p1, sdl::Point const& p2, NullableColor const& color) {
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  Color renderer_color{};
  if (color) {
    renderer_color = get_renderer_color();
    set_renderer_color(color.value());
  }
  const auto ret = SDL_RenderDrawLine(renderer_, p1.x, p1.y, p2.x, p2.y);
  if (ret != 0) {
    throw sdl::RenderingError{SDL_GetError()};
  }
  if (color) {
    set_renderer_color(renderer_color);
  }
}

void sdl::Window::update() {
  SDL_RenderPresent(renderer_);
  SDL_RenderClear(renderer_);
}

sdl::Color sdl::Window::get_renderer_color() const {
  assert(renderer_ && "Null renderer");
  Color color{};
  const auto ret = SDL_GetRenderDrawColor(renderer_, &color.r, &color.g, &color.b, &color.a);
  if (ret != 0) {
    throw std::runtime_error{SDL_GetError()};
  }
  return color;
}

void sdl::Window::set_renderer_color(Color const& color) {
  assert(renderer_ && "Null renderer");
  const auto ret = SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
  if (ret != 0) {
    throw std::runtime_error{SDL_GetError()};
  }
}

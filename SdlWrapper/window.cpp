#include "window.h"

#include <algorithm> // std::copy
#include <stdexcept> // std::runtime_error

sdl::Window::Window(std::string const& name, Size const& size, flag_t flags)
  : Window(SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.w, size.h, flags), renderer::ACCELERATED){
}

sdl::Window::Window(std::string const& name, Point const& coords, Size const& size, flag_t flags)
	: Window(SDL_CreateWindow(name.c_str(), coords.x, coords.y, size.w, size.h, flags), renderer::ACCELERATED){
	
}

sdl::Window::Window(std::string const& name, Rect const& rect, flag_t flags)
	: Window(SDL_CreateWindow(name.c_str(), rect.x, rect.y, rect.w, rect.h, flags), renderer::ACCELERATED){

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

void sdl::Window::blit(Surface const& surface, Point const& coords, NullableRect const& src_rect) const{
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

void sdl::Window::blit(Texture const& texture, Point const& coords, NullableRect const& src_rect) const{
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  assert(w > 0 && "Invalid texture width");
  assert(h > 0 && "Invalid texture height");
  const SDL_Rect src = (src_rect) ? src_rect.value() : Rect{0, 0, static_cast<unsigned>(w), static_cast<unsigned>(h)};
  const SDL_Rect dest = {coords.x, coords.y, src.w, src.h};
  const auto ret = SDL_RenderCopy(renderer_, texture, &src, &dest);
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::Window::blit(internal::IDrawable const& drawable, Point const& coords, NullableRect const& src_rect) const{
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  drawable.on_window(*this, coords, src_rect);
}

void sdl::Window::draw_point(sdl::Point const& point){
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  const auto ret = SDL_RenderDrawPoint(renderer_, point.x, point.y);
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::Window::draw_points(std::vector<sdl::Point> const& points){
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  const auto size = points.size();
  std::vector<SDL_Point> raw_points(size);
  /*for(auto i = 0u; i < size; i++){
    raw_points[i] = points[i];
  }*/
  std::copy(points.begin(), points.end(), raw_points.begin());
  const auto ret = SDL_RenderDrawPoints(renderer_, raw_points.data(), raw_points.size());
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::Window::draw_line(sdl::Point const& p1, sdl::Point const& p2){
  assert(*this && "Null window");
  assert(renderer_ && "Null renderer");
  const auto ret = SDL_RenderDrawLine(renderer_, p1.x, p1.y, p2.x, p2.y);
  if(ret != 0){
    throw std::runtime_error{SDL_GetError()};
  }
}

void sdl::Window::update(){
  SDL_RenderPresent(renderer_);
  SDL_RenderClear(renderer_);
}
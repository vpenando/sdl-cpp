#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <memory> // std::unique_ptr
#include <string> // std::string

#include <SDL.h>     // SDL_Window, SDL_DestroyWindow

#include "base.h"     // internal::memory::Base
#include "nullable.h" // internal::Nullable
#include "rect.h"     // sdl::Rect
#include "size.h"     // Size
#include "surface.h"  // sdl::Surface
#include "vector2.h"  // Vector2

namespace sdl{
  namespace internal{
    using BaseWindow = Base<SDL_Window, SDL_DestroyWindow>;
    using Renderer = Base<SDL_Renderer, SDL_DestroyRenderer>;
  } // namespace sdl::internal

  using Screen = Surface;

  // SDL_Window wrapper
  class Window final : public internal::BaseWindow{
    using flag_t = Uint32;
    using NullableRect = internal::Nullable<Rect>;
  public:
    // Ctor
    using internal::BaseWindow::BaseWindow;
    Window(std::string const& name, Size const& size, flag_t flags = 0u,
      Vector2i const& pos = Vector2i{},
      SDL_RendererFlags renderer_flags = SDL_RENDERER_ACCELERATED);
    explicit Window(SDL_Window *window, Size const& size, SDL_RendererFlags renderer_flags = SDL_RENDERER_ACCELERATED);
    Size size() const noexcept;
    void blit(Surface const& surface, Rect const& rect, NullableRect const& opt_rect = internal::NULL_VAL);
    void update();

  private:
    Size size_;
    internal::Renderer renderer_;
    Screen screen_;
  };

} // namespace sdl

#endif // __WINDOW_H__
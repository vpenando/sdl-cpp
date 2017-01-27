#ifndef __WINDOW_H__
#define __WINDOW_H__

// **********************
// ** Standard library **
//***********************
#include <memory> // std::unique_ptr
#include <string> // std::string
#include <vector> // std::vector

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Window, SDL_DestroyWindow, SDL_Renderer, SDL_DestroyRenderer

// **********************
// ** Custom lib files **
// **********************
#include "base.h"     // sdl::internal::memory::Base
#include "color.h"    // sdl::Color
#include "nullable.h" // sdl::internal::Nullable
#include "rect.h"     // sdl::Rect
#include "size.h"     // sdl::Size
#include "surface.h"  // sdl::Surface
#include "point.h"    // sdl::Point

namespace sdl{
  namespace renderer{
    constexpr auto SOFTWARE = SDL_RENDERER_SOFTWARE;
    constexpr auto ACCELERATED = SDL_RENDERER_ACCELERATED;
    constexpr auto PRESENTVSYNC = SDL_RENDERER_PRESENTVSYNC;
    constexpr auto TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE;
  } // namespace std::renderer

  namespace internal{
    class IDrawable;
    using BaseWindow = Base<SDL_Window, SDL_DestroyWindow>;
    using BaseRenderer = Base<SDL_Renderer, SDL_DestroyRenderer>;
  } // namespace sdl::internal

  //using Renderer = internal::Base<SDL_Renderer, SDL_DestroyRenderer>;
  using Texture = internal::Base<SDL_Texture, SDL_DestroyTexture>;

  class Renderer final : public internal::BaseRenderer{
  public:
    explicit Renderer(SDL_Renderer *renderer, Color const& color = Color::BLACK) : internal::BaseRenderer(renderer){
      SDL_SetRenderDrawColor(*this, color.r, color.g, color.b, color.a);
    }
  };

  // SDL_Window wrapper
  class Window final : public internal::BaseWindow{
    using flag_t = Uint32;
    using NullableRect = internal::Nullable<Rect>;
  public:
    // Ctor
    using internal::BaseWindow::BaseWindow;
    Window(std::string const& name, Size const& size, flag_t flags = 0u);
    Window(std::string const& name, Point const& coords, Size const& size, flag_t flags = 0u);
    Window(std::string const& name, Rect const& rect, flag_t flags = 0u);
    Window(SDL_Window *window, int renderer_flags = renderer::ACCELERATED);
    Size size() const noexcept;
    void blit(Surface const& surface, Point const& coords, NullableRect const& src_rect = internal::NULL_VAL) const;
    void blit(Texture const& texture, Point const& coords, NullableRect const& src_rect = internal::NULL_VAL) const;
    void blit(internal::IDrawable const& drawable, Point const& coords, NullableRect const& src_rect = internal::NULL_VAL) const;
    void draw_point(Point const& point);
    void draw_points(std::vector<Point> const& points);
    void draw_line(Point const& p1, Point const& p2);
    void update();
    
  private:
    Size size_;
    Renderer renderer_;
  };

  namespace internal{
    class IDrawable{
      friend class Window;
      using NullableRect = Nullable<Rect>;
    public:
      IDrawable() = default;
      virtual ~IDrawable() = default;

    private:
      virtual void on_window(Window const& window, Point const& coords, NullableRect const& src_rect = NULL_VAL) const = 0;
    };

  } // namespace sdl::internal
} // namespace sdl

#endif // __WINDOW_H__
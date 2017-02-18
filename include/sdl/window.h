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
#include <sdl/color.h>              // sdl::Color
#include <sdl/api/nullable.h>       // sdl::api::Nullable
#include <sdl/rect.h>               // sdl::Rect
#include <sdl/size.h>               // sdl::Size
#include <sdl/surface.h>            // sdl::Surface
#include <sdl/point.h>              // sdl::Point
#include <sdl/api/memory/wrapper.h> // sdl::api::memory::Wrapper

namespace sdl{
  namespace renderer{
    constexpr auto SOFTWARE = SDL_RENDERER_SOFTWARE;
    constexpr auto ACCELERATED = SDL_RENDERER_ACCELERATED;
    constexpr auto PRESENTVSYNC = SDL_RENDERER_PRESENTVSYNC;
    constexpr auto TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE;
  } // namespace std::renderer

  namespace api{
    class IDrawable;
    using BaseWindow = memory::Wrapper<SDL_Window, SDL_DestroyWindow>;
    using BaseRenderer = memory::Wrapper<SDL_Renderer, SDL_DestroyRenderer>;
  } // namespace sdl::api

  //using Renderer = api::Base<SDL_Renderer, SDL_DestroyRenderer>;
  using Texture = api::memory::Wrapper<SDL_Texture, SDL_DestroyTexture>;

  class Renderer final : public api::BaseRenderer{
  public:
    explicit Renderer(SDL_Renderer *renderer, Color const& color = Color::BLACK) : api::BaseRenderer(renderer){
      SDL_SetRenderDrawColor(*this, color.r, color.g, color.b, color.a);
    }
  };

  struct WindowProperties final{
    using flag_t = Uint32;
    WindowProperties(std::string const& n, Size const& s, flag_t f, int rf,
      api::Nullable<Point> np = api::NULL_VAL,
      api::Nullable<SDL_Surface*> ns = api::NULL_VAL);
    ~WindowProperties();
    std::string name;
    Size size;
    flag_t flags;
    int renderer_flags;
    api::Nullable<Point> pos;
    api::Nullable<SDL_Surface*> icon;
  };

  // SDL_Window wrapper
  class Window final : public api::BaseWindow{
    using flag_t = Uint32;
    using NullableRect = api::Nullable<Rect>;
  public:
    // Ctor
    using api::BaseWindow::BaseWindow;
    Window(std::string const& name, Size const& size, flag_t flags = 0u);
    Window(std::string const& name, Point const& coords, Size const& size, flag_t flags = 0u);
    Window(std::string const& name, Rect const& rect, flag_t flags = 0u);
    Window(SDL_Window *window, int renderer_flags = renderer::ACCELERATED);
    Size size() const noexcept;
    void blit(Surface const& surface, Point const& coords, NullableRect const& src_rect = api::NULL_VAL) const;
    void blit(Texture const& texture, Point const& coords, NullableRect const& src_rect = api::NULL_VAL) const;
    void blit(api::IDrawable const& drawable, Point const& coords, NullableRect const& src_rect = api::NULL_VAL) const;
    void draw_point(Point const& point);
    void draw_points(std::vector<Point> const& points);
    void draw_line(Point const& p1, Point const& p2);
    void update();
    
  private:
    Size size_;
    Renderer renderer_;
  };

  namespace api{
    class IDrawable{
      friend class ::sdl::Window;
      using NullableRect = Nullable<Rect>;
    public:
      IDrawable() = default;
      virtual ~IDrawable() = default;

    private:
      virtual void on_window(Window const& window, Point const& coords, NullableRect const& src_rect = NULL_VAL) const = 0;
    };

  } // namespace sdl::api
} // namespace sdl

#endif // __WINDOW_H__

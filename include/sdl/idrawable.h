#ifndef __IDRAWABLE_H__
#define __IDRAWABLE_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/nullable.h> // sdl::api::Nullable
#include <sdl/point.h>        // sdl::Point
#include <sdl/rect.h>         // sdl::Rect

namespace sdl {

  class Window;
  
  class IDrawable {
    friend class Window;
  protected:
    using NullableRect = api::Nullable<Rect>;
  public:
    IDrawable() = default;
    virtual ~IDrawable() = default;

  private:
    // Will be called in Window::blit(IDrawable const&)
    virtual void on_window(Window& window, Point const& coords, NullableRect const& src_rect = api::NULL_VAL) const = 0;
  };

} // namespace sdl

#endif // __IDRAWABLE_H__

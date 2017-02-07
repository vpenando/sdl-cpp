#ifndef __MOUSE_H__
#define __MOUSE_H__

// **********************
// ** Standard library **
//***********************
// - 

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_GetMouseState, Uint32

// **********************
// ** Custom lib files **
// **********************
#include "ihandler.h" // sdl::internal::IHandler
#include "point.h"    // sdl::Point

namespace sdl{

  enum ClickCode{
    Left = SDL_BUTTON(SDL_BUTTON_LEFT),
    Right = SDL_BUTTON(SDL_BUTTON_RIGHT),
    Middle = SDL_BUTTON(SDL_BUTTON_MIDDLE)
  };

  struct MouseState final{
  public:
    MouseState(Point const& coords, Uint32 state) noexcept;
    Point coords() const noexcept;
    bool clicked(ClickCode c) const noexcept;
  private:
    sdl::Point coords_;
    Uint32 state_;
  };

  class MouseStateHandler final :
    public internal::IHandler<sdl::MouseState>,
    public ecs::Component
  {
  public:
    MouseStateHandler(bool read_events = false);
    void update() override;
    sdl::MouseState state() const override;
  private:
    bool read_events_;
    sdl::MouseState state_;
  };


  //MouseState state(bool read_events = false) noexcept;

} // namespace sdl

#endif // __MOUSE_H__
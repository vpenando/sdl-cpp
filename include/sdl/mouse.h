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
#include <sdl/api/ihandler.h> // sdl::api::IHandler
#include <sdl/ecs/ecs.h>      // sdl::ecs::Component
#include <sdl/point.h>        // sdl::Point

//! @namespace sdl
//! @brief The SDL wrapper main namespace
namespace sdl {

  //! @enum  ClickCode
  //! @brief The mouse click codes
  enum ClickCode {
    Left = SDL_BUTTON(SDL_BUTTON_LEFT),    //!< The left click
    Right = SDL_BUTTON(SDL_BUTTON_RIGHT),  //!< The right click
    Middle = SDL_BUTTON(SDL_BUTTON_MIDDLE) //!< The middle click
  };

  //! @class MouseState
  //! @brief Represents the mouse state
  struct MouseState final {
  public:
    MouseState(Point const& coords, Uint32 state) noexcept;
    Point coords() const noexcept;
    bool clicked(ClickCode c) const noexcept;

  private:
    sdl::Point coords_;
    Uint32 state_;
  };

  //! @class MouseStateHandler
  //! @brief Handles the mouse state
  //! @extends api::IHandler
  //! @extends ecs::Component
  class MouseStateHandler final :
    public api::IHandler<sdl::MouseState>,
    public ecs::Component
  {
  public:
    explicit MouseStateHandler(bool read_events = false);  
    void update() override;   
    sdl::MouseState state() const override;

  private:
    bool read_events_;
    sdl::MouseState state_;
  };

} // namespace sdl

sdl::ClickCode operator|(sdl::ClickCode const&, sdl::ClickCode const&) = delete;
sdl::ClickCode operator&(sdl::ClickCode const&, sdl::ClickCode const&) = delete;

#endif // __MOUSE_H__

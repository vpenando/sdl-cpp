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
    //! @brief Ctor
    //! @param coords The X and Y coords
    //! @param state  The mouse state (returned by SDL_GetMouseState)
    MouseState(Point const& coords, Uint32 state) noexcept;
    //! @brief Returns the mouse coords
    Point coords() const noexcept;
    //! @brief Returns true if the button corresponding to the given clickcode is clicked
    //! @param c The clickcode corresponding to the button we want to test
    bool clicked(ClickCode c) const noexcept;
  private:
    sdl::Point coords_;
    Uint32 state_;
  };

  //! @class MouseStateHandler
  //! @brief Handles the mouse state
  //! @extends IHandler
  //! @extends Component
  class MouseStateHandler final :
    public api::IHandler<sdl::MouseState>,
    public ecs::Component
  {
  public:
    //! @brief Ctor
    //! @param read_events True if we want the MouseStateHandler to pump events (SDL_PumpEvents)
    MouseStateHandler(bool read_events = false);
    //! @brief Update the mouse state
    void update() override;
    //! @brief   The mouse state
    //! @returns A MouseState corresponding to the current mouse state
    sdl::MouseState state() const override;
  private:
    bool read_events_;
    sdl::MouseState state_;
  };

} // namespace sdl

#endif // __MOUSE_H__

#include <sdl/mouse.h>

//! @brief Ctor
//! @param coords The X and Y coords
//! @param state  The mouse state (returned by SDL_GetMouseState)
sdl::MouseState::MouseState(Point const& coords, Uint32 state) noexcept
  : coords_{coords}, state_{state}
{
}

//! @brief Returns the mouse coords
sdl::Point sdl::MouseState::coords() const noexcept {
  return coords_;
}

//! @brief Returns true if the button corresponding to the given clickcode is clicked
//! @param c The clickcode corresponding to the button we want to test
bool sdl::MouseState::clicked(sdl::ClickCode c) const noexcept {
  return (state_ & c) != 0;
}

//! @brief Ctor
//! @param read_events True if we want the MouseStateHandler to pump events (SDL_PumpEvents)
sdl::MouseStateHandler::MouseStateHandler(bool read_events)
  : read_events_{read_events},
  state_{sdl::Point{0, 0}, 0}
{
}

//! @brief Update the mouse state
void sdl::MouseStateHandler::update() {
  if (read_events_) {
    SDL_PumpEvents();
  }
  sdl::Point coords{};
  const auto ret = SDL_GetMouseState(&coords.x, &coords.y);
  state_ = sdl::MouseState{coords, ret};
}

//! @brief   The mouse state
//! @returns A MouseState corresponding to the current mouse state
sdl::MouseState sdl::MouseStateHandler::state() const {
  return state_;
}

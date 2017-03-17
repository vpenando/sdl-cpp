#include <sdl/mouse.h>

sdl::MouseState::MouseState(Point const& coords, Uint32 state) noexcept
  : coords_{coords}, state_{state}
{
}

sdl::Point sdl::MouseState::coords() const noexcept {
  return coords_;
}

bool sdl::MouseState::clicked(sdl::ClickCode c) const noexcept {
  return (state_ & c) != 0;
}

sdl::MouseStateHandler::MouseStateHandler(bool read_events)
  : read_events_{read_events},
  state_{sdl::Point{0, 0}, 0}
{
}

void sdl::MouseStateHandler::update() {
  if (read_events_) {
    SDL_PumpEvents();
  }
  sdl::Point coords{};
  const auto ret = SDL_GetMouseState(&coords.x, &coords.y);
  state_ = sdl::MouseState{coords, ret};
}

sdl::MouseState sdl::MouseStateHandler::state() const {
  return state_;
}

#include "keyboard.h"

#include <algorithm> // std::copy

sdl::KeyboardState::KeyboardState(std::vector<Uint8> const& state) : state_{state}{

}

sdl::Key sdl::KeyboardState::operator[](sdl::KeyCode code) const{
  const auto scan_code = SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(code));
  const bool pressed = state_[scan_code] != 0;
  return sdl::Key{code, pressed};
}

sdl::KeyboardStateHandler::KeyboardStateHandler(bool read_events)
  : read_events_{read_events} {
  update();
}

sdl::KeyboardState sdl::KeyboardStateHandler::state() const{
  return state_;
}

void sdl::KeyboardStateHandler::update(){
  if(read_events_){
    SDL_PumpEvents();
  }
  int size = 0;
  const auto* state_ptr = SDL_GetKeyboardState(&size);
  state_ = std::vector<Uint8>(size);
  std::copy(state_ptr, state_ptr+size, state_.begin());
}

#include <sdl/keyboard.h>

#include <algorithm> // std::copy
#include <cassert>   // assert

sdl::KeyboardState::KeyboardState(std::vector<Uint8> const& state)
  : state_{state}
{
}

sdl::Key sdl::KeyboardState::operator[](sdl::KeyCode code) const{
  const auto scan_code = SDL_GetScancodeFromKey(static_cast<SDL_Keycode>(code));
  assert(static_cast<size_type>(scan_code) < state_.size() && "Out of bounds");
  const bool pressed = state_[scan_code] != 0;
  return sdl::Key{code, pressed};
}

sdl::Key sdl::KeyboardState::operator[](SDL_Keycode code) const{
  return (*this)[static_cast<sdl::KeyCode>(code)];
}

sdl::KeyboardStateHandler::KeyboardStateHandler(bool read_events)
  : read_events_{read_events}
{
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
  const auto* state_ptr = SDL_GetKeyboardState(&size); // api SDL pointer: no need to free it
  assert(size > 0 && "Invalid size");
	using Size = typename std::vector<Uint8>::size_type;
  state_ = std::vector<Uint8>(static_cast<Size>(size));
  std::copy(state_ptr, state_ptr+size, state_.begin());
}

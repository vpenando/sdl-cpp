#include <sdl/mouse.h>

enum SdlClick{
  Left = SDL_BUTTON(SDL_BUTTON_LEFT),
  Right = SDL_BUTTON(SDL_BUTTON_RIGHT),
  Middle = SDL_BUTTON(SDL_BUTTON_MIDDLE)
};

template<SdlClick c>
inline bool clicked(int state) noexcept{
  return (state & c) != 0;
}

sdl::MouseState::MouseState(Point const& coords, Uint32 state) noexcept
  : coords_{coords}, state_{state}
{
}

sdl::Point sdl::MouseState::coords() const noexcept{
  return coords_;
}

bool sdl::MouseState::clicked(sdl::ClickCode c) const noexcept{
  return (state_ & c) != 0;
}

//sdl::mouse::MouseState sdl::mouse::state(bool read_events) noexcept{
//  int x;
//  int y;
//  if(read_events){
//    SDL_PumpEvents();
//  }
//  const auto ret = SDL_GetMouseState(&x, &y);
//  const sdl::Point coords{x, y};
//  return sdl::mouse::MouseState{coords, ret};
//}

sdl::MouseStateHandler::MouseStateHandler(bool read_events)
  : read_events_{read_events},
  state_{sdl::Point{0, 0}, 0}{

}

void sdl::MouseStateHandler::update(){
  int x;
  int y;
  if(read_events_){
    SDL_PumpEvents();
  }
  const auto ret = SDL_GetMouseState(&x, &y);
  const sdl::Point coords{x, y};
  state_ = sdl::MouseState{coords, ret};
}

sdl::MouseState sdl::MouseStateHandler::state() const{
  return state_;
}
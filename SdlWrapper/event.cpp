//#include "event.h"
//
//#include <stdexcept> // std::runtime_error
//
//void sdl::Event::poll(){
//  if(SDL_PollEvent(&event_)){
//    throw std::runtime_error{SDL_GetError()};
//  }
//}
//
//sdl::Event::operator SDL_Event() const noexcept{
//  return event_;
//}
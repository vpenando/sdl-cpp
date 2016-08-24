#ifndef __SDL_INIT_H__
#define __SDL_INIT_H__

#include "base.h"
#include "window.h"

#undef main

namespace sdl{
  namespace init{
    constexpr auto TIMER = SDL_INIT_TIMER;
    constexpr auto AUDIO = SDL_INIT_AUDIO;
    constexpr auto VIDEO = SDL_INIT_VIDEO;
    constexpr auto JOYSTICK = SDL_INIT_JOYSTICK;
    constexpr auto HAPTIC = SDL_INIT_HAPTIC;
    constexpr auto GAMECONTROLLER = SDL_INIT_GAMECONTROLLER;
    constexpr auto EVENTS = SDL_INIT_EVENTS;
    constexpr auto NOPARACHUTE = SDL_INIT_NOPARACHUTE;
    constexpr auto EVERYTHING = SDL_INIT_EVERYTHING;
  } // namespace std::init

} // namespace sdl

#endif // __SDL_INIT_H__
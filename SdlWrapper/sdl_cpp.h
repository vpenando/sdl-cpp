#ifndef __SDL_INIT_H__
#define __SDL_INIT_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include "base.h"        // sdl::Base
#include "noncopyable.h" // sdl::internal::NonCopyable
#include "window.h"      // sdl::Window

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
  } // namespace sdl::init

  class Context : internal::NonCopyable{
  public:
    Context(unsigned flags = 0);
    ~Context();
  };

} // namespace sdl

#endif // __SDL_INIT_H__
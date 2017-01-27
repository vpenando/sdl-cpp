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
#include "ecs.h"         // sdl::ecs::Component
#include "noncopyable.h" // sdl::internal::NonCopyable
#include "window.h"      // sdl::Window

#undef main

namespace sdl{
  enum init{
    TIMER = SDL_INIT_TIMER,
    AUDIO = SDL_INIT_AUDIO,
    VIDEO = SDL_INIT_VIDEO,
    JOYSTICK = SDL_INIT_JOYSTICK,
    HAPTIC = SDL_INIT_HAPTIC,
    GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
    EVENTS = SDL_INIT_EVENTS,
    NOPARACHUTE = SDL_INIT_NOPARACHUTE,
    EVERYTHING = SDL_INIT_EVERYTHING
  }; // namespace sdl::init

  class Context : internal::NonCopyable, public ecs::BaseComponent{
  public:
    Context(unsigned flags = 0);
    ~Context();
  };

} // namespace sdl

#endif // __SDL_INIT_H__
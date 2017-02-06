#ifndef __EVENT_H__
#define __EVENT_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
#include <cassert> // assert
#include <SDL.h>   // SDL_Surface, SDL_FreeSurface

// **********************
// ** Custom lib files **
// **********************
#include "keyboard.h" // sdl::KeyboardStateHandler
#include "mouse.h"    // sdl::MouseStateHandler

namespace sdl{

  using Event = SDL_Event;

  inline int poll_event(Event *e){
    assert(e && "Null pointer");
    return SDL_PollEvent(e);
  }

  class EventHandler final : protected ecs::BaseComponent{
  public:
    EventHandler(bool read_events = true);
    void update();
    using ecs::BaseComponent::get;

  private:
    KeyboardStateHandler& keyboard_handler_;
    MouseStateHandler& mouse_handler_;
  };

} // namespace sdl

#endif // __EVENT_H__
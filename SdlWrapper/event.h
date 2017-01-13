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
// -

namespace sdl{

  using Event = SDL_Event;

  inline int poll_event(Event *e){
    assert(e && "Null pointer");
    return SDL_PollEvent(e);
  }

} // namespace sdl

#endif // __EVENT_H__
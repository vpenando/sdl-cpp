#ifndef __EVENT_H__
#define __EVENT_H__

// **********************
// ** Standard library **
//***********************
#include <cassert>    // assert
#include <functional> // std::function
#include <map>        // std::map

// **********************
// ** SDL header files **
// **********************
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
    EventHandler();
    template<class T>
    T& get();
    void update();
    void on_quit(std::function<void(void)> const& fun);
    void on_press(KeyCode code, std::function<void(void)> const& fun);

  private:
    //using ecs::BaseComponent::get;
    KeyboardStateHandler& keyboard_handler_;
    MouseStateHandler& mouse_handler_;
    std::function<void(void)> on_quit_;
    bool on_quit_defined_;
    std::map<KeyCode, std::function<void(void)>> actions_;
  };

  template<class T>
  T& EventHandler::get(){
    static_assert(std::is_base_of<sdl::internal::Handler, T>::value, "Expected a Handler type");
    return ecs::BaseComponent::get<T>();
  }

} // namespace sdl

#endif // __EVENT_H__
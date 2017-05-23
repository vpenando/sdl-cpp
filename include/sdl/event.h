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
#include <SDL.h> // SDL_Surface, SDL_FreeSurface

// **********************
// ** Custom lib files **
// **********************
#include <sdl/ecs/ecs.h>
#include <sdl/keyboard.h> // sdl::KeyboardStateHandler
#include <sdl/mouse.h>    // sdl::MouseStateHandler

namespace sdl {

  using Event = SDL_Event;

  inline int poll_event(Event *e) {
    assert(e && "Null pointer");
    return SDL_PollEvent(e);
  }

  namespace api {
    using BaseHandlerComponent = ecs::api::RootComponent<sdl::api::IUpdatable>;
  } // namespace sdl::api

  class EventHandler final : private api::BaseHandlerComponent {
    using Action = std::function<void(void)>;
  public:
    EventHandler();
    using api::BaseHandlerComponent::get;
    void update();
    void on_quit(Action const& fun);
    void on_press(KeyCode code, Action const& fun);
    void on_click(ClickCode code, Action const& fun);
    
  private:
    void handle_actions();
    KeyboardStateHandler& keyboard_handler_;
    MouseStateHandler& mouse_handler_;
    std::function<void(void)> on_quit_;
    bool on_quit_defined_;
    std::map<KeyCode, Action> key_actions_;
    std::map<ClickCode, Action> click_actions_;
  };

} // namespace sdl

#endif // __EVENT_H__

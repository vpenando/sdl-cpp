#include "event.h"


sdl::EventHandler::EventHandler(bool read_events)
  : keyboard_handler_(add<KeyboardStateHandler>(read_events)),
  mouse_handler_(add<MouseStateHandler>(read_events)){

}

void sdl::EventHandler::update(){
  keyboard_handler_.update();
  mouse_handler_.update();
}
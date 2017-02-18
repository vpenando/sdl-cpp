#include <sdl/event.h>

sdl::EventHandler::EventHandler()
  : keyboard_handler_(add<KeyboardStateHandler>(false)),
  mouse_handler_(add<MouseStateHandler>(false)),
  on_quit_defined_(false)
{
}

void sdl::EventHandler::on_quit(Action const& fun){
  assert(!on_quit_defined_ && "Already defined");
  on_quit_ = fun;
  on_quit_defined_ = true;
}

void sdl::EventHandler::update(){
  if(!on_quit_defined_){
    throw std::runtime_error{"You must bind an exit function by calling EventHandler::on_quit before using it"};
  }
  sdl::Event e;
  while(SDL_PollEvent(&e)){
    if(e.type == SDL_QUIT){
      on_quit_();
    }
  }
  keyboard_handler_.update();
  mouse_handler_.update();
  if(actions_.size() > 0){
    const auto keyboard_state = keyboard_handler_.state();
    for(auto& pair : actions_){
      if(keyboard_state[pair.first].pressed){
        pair.second();
      }
    }
  }
}

void sdl::EventHandler::on_press(sdl::KeyCode code, Action const& fun){
  actions_.insert(std::pair<KeyCode, Action>(code, fun));
}
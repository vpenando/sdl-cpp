#include <functional> // std::function
#include <iostream>   // std::cout

#include <sdl/sdl_cpp.h>

int main(int, char **) {
  sdl::EventHandler handler;
  bool loop = true;
  handler.on_quit([&loop](){ loop = false; });
  handler.on_press(sdl::KeyCode::A, [](){
    std::cout << "Key A pressed" << std::endl;
  });
  auto& mouse_handler = handler.get<sdl::MouseStateHandler>();
  while (loop) {
    const auto mouse_state  = mouse_handler.state();
    const auto mouse_coords = mouse_state.coords();
    std::cout << "Mouse: (" << mouse_coords.x << ", " << mouse_coords.y << ")" << std::endl;
    // Update
    handler.update(); // Will also update mouse_handler
  }
}

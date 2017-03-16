#include <functional> // std::function
#include <iostream>   // std::cout, std::cin, std::endl
#include <stdexcept>  // std::runtime_error

#include <sdl/sdl_cpp.h>

int main(int, char **){
  try{
    // Init
    sdl::init(sdl::INIT_VIDEO);
    // Window
    sdl::Window window{"My Window", sdl::Size{500, 500}};
    bool loop = true;
    // Event handler
    sdl::EventHandler handler;
    handler.on_quit([&loop](){ loop = false; });
    handler.on_press(sdl::KeyCode::A, [](){
      std::cout << "Key A pressed" << std::endl;
    });
    auto& mouse_handler = handler.get<sdl::MouseStateHandler>();
    while(loop){
      // Example:
      const auto mouse_coords = mouse_handler.coords();
      std::cout << "Mouse: (" << mouse_coords.x << ", " << mouse_coords.y << ")" << std::endl;
      // Update
      window.update();
      handler.update();
    }

  } catch(std::exception const& e){
    std::cout << "Error: " << e.what();
  }
  SDL_Quit();
}

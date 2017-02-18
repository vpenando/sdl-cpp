#include <iostream>

#include <sdl/ecs/ecs.h>
#include <sdl/sdl_cpp.h>
#include <sdl/window.h>
#include <functional>
#include <sdl/event.h>
#include <sdl/mouse.h>
#include <sdl/keyboard.h>
#include <sdl/event.h>

void foo(int*){
  std::cout << "lel";
}

void bar(SDL_Window*){
  std::cout << "bar";
}

int main(){
  try{
    // Initialisation
    const auto ret = SDL_Init(sdl::INIT_VIDEO);
    if(ret){
      throw std::runtime_error{"Cannot init SDL (status: " + std::to_string(ret) + ")"};
    }
    // Création de la fenêtre
    sdl::Window window{"My Window", sdl::Size{500, 500}};
    // Création de la surface
    sdl::Surface surface{SDL_LoadBMP("moderne.bmp")};
    SDL_SetWindowIcon(window, surface);
    const auto surface_size = surface.size();
    bool loop = true;
    sdl::EventHandler handler;
    handler.on_quit([&loop](){ loop = false; });
    handler.on_press(sdl::KeyCode::A, [](){
      std::cout << "Key A pressed" << std::endl;
    });
    auto& mouse_handler = handler.get<sdl::MouseStateHandler>();
    while(loop){
      // Calcul des coordonnées
      const auto mouse_state = mouse_handler.state();
      const auto mouse_coords = mouse_state.coords();
      const auto point = sdl::Point{
        static_cast<int>(mouse_coords.x - surface_size.w) / 2,
        static_cast<int>(mouse_coords.y - surface_size.h) / 2
      };
      // Affichage
      window.blit(surface, point);
      window.update();
      handler.update();
    }

  } catch(std::exception const& e){
    std::cout << "Une erreur est survenue : " << e.what();
  }
  SDL_Quit();
}


/*
 * #include <SDL.h>
#undef main
int main(){
  SDL_Window* window = NULL;
  window = SDL_CreateWindow
  (
    "Jeu de la vie", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    640,
    480,
    SDL_WINDOW_SHOWN
  );

  // Setup renderer
  SDL_Renderer* renderer = NULL;
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Set render color to red ( background will be rendered in this color )
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

  // Clear winow
  SDL_RenderClear(renderer);

  // Creat a rect at pos ( 50, 50 ) that's 50 pixels wide and 50 pixels high.
  SDL_Rect r;
  r.x = 50;
  r.y = 50;
  r.w = 50;
  r.h = 50;

  // Set render color to blue ( rect will be rendered in this color )
  SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

  // Render rect
  SDL_RenderFillRect(renderer, &r);

  // Render the rect to the screen
  SDL_RenderPresent(renderer);

  // Wait for 5 sec
  SDL_Delay(5000);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
 */

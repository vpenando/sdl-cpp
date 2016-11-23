#include <iostream>

#include "ecs.h"
#include "sdl_cpp.h"
#include "window.h"
#include <functional>

void foo(int*){
  std::cout << "lel";
}

void bar(SDL_Window*){
  std::cout << "bar";
}

class Foo : public sdl::internal::ecs::Component{
public:
  Foo(int i, bool b, char c):i_(i), b_(b), c_(c){}
  int i_;
  bool b_;
  char c_;
};
int main(){
  sdl::internal::ecs::BaseComponent c;
  auto& c2 = c.add<Foo>(42, true, 'c');
  std::cout << c2.i_;
  const auto contains = c.contains<Foo>([](Foo const& f) -> bool{return f.i_ == 42; });
  sdl::Window window("toto", sdl::Size{500, 500});
  //auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  sdl::Surface surface{SDL_LoadBMP("moderne.bmp")};
  //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  //SDL_RenderClear(renderer);
  //SDL_RenderPresent(renderer);
  bool loop = true;
  while(loop){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
      if(e.type == SDL_QUIT)
        loop = false;
      else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
        break;
    }

    window.blit(surface, sdl::Point{50, 50});
    window.update();
  }
  
  //std::cin.get();
  bar(window);
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
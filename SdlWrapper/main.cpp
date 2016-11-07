#include <iostream>

#include "sdl_cpp.h"
#include "window.h"

void foo(int*){
  std::cout << "lel";
}

void bar(SDL_Window*){
  std::cout << "bar";
}

int main(){
  sdl::Window window("toto", sdl::Size{500, 500}, 0, sdl::Vector2i{100, 100});
  //auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  sdl::Surface surface{SDL_LoadBMP("moderne.bmp")};
  //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
  //SDL_RenderClear(renderer);
  //SDL_RenderPresent(renderer);
  window.blit(surface, sdl::Vector2i{0, 0});
  
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
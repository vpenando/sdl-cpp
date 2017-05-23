#include <sdl/sdl_cpp.h>

int main(int, char **) {
  // Window
  sdl::Window window{"My Window", sdl::Size{500, 500}};
  bool loop = true;
  while (loop) {
    window.blit(/* sdl::Surface */,   sdl::Point{/* x, y */});
    window.blit(/* sdl::Texture */,   sdl::Point{/* x, y */});
    window.blit(/* sdl::IDrawable */, sdl::Point{/* x, y */});
    window.draw_point(/* sdl::Point */);
    window.draw_points(/* std::vector<Point> */);
    window.draw_line(/* sdl::Point */, /* sdl::Point */); // (x1, y1), (x2, y2)
    // Update
    window.update();
  }
}

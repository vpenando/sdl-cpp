# sdl-cpp (Work in progress!) [![Build Status](https://travis-ci.org/tyr-sl3/sdl-cpp.svg)](https://travis-ci.org/tyr-sl3/sdl-cpp)

RAII-conform SDL wrapper written in C++14 by Vincent P. This wrapper is compatible with C SDL2 code; each RAII-conform SDL entity is convertible to its C equivalent:
```cpp
void foo(SDL_Window *window){
  // ...
}
// ...
sdl::Window window{"My Window", sdl::Size{500, 500}};
foo(window); // Ok!
```

# Build status by branch & OS
 OS / Branch | master | dev
---|-------|------------------
**Linux** | [![Build Status](https://api.travis-ci.org/tyr-sl3/sdl-cpp.svg?branch=master)](https://travis-ci.org/tyr-sl3/sdl-cpp?branch=master) | [![Build Status](https://api.travis-ci.org/tyr-sl3/sdl-cpp.svg?branch=dev)](https://travis-ci.org/tyr-sl3/sdl-cpp?branch=dev)
**Window** | *Soon...* | *Soon...*

# Conversion matrix:
SDL C type | Wrapper type
-----------|-------------
`SDL_Color` | `sdl::Color`
`SDL_Point` | `sdl::Point`
`SDL_Rect` | `sdl::Rect`
`SDL_Surface*` | `sdl::Surface`
`SDL_Texture*`| `sdl::Texture`
`SDL_Window*`| `sdl::Window`

Note: `sdl::Event` is just an alias of `SDL_Event`.

# Examples
Note: See `src/main.cpp` for a basic example.

### Creating a window
The simpliest way:
```cpp
sdl::Window window{"My Window", sdl::Size{500, 500}};
```
`sdl::Window` has some other constructors:
```cpp
Window(SDL_Window *window); // Inherited from sdl::api::Wrapper<T, Deleter<T>>
Window(std::string const& name, Size const& size, flag_t flags = 0u);
Window(std::string const& name, Point const& coords, Size const& size, flag_t flags = 0u);
Window(std::string const& name, Rect const& rect, flag_t flags = 0u);
Window(SDL_Window *window, unsigned renderer_flags = renderer::ACCELERATED);
```

### Displaying an image
Now that you have a window, you may want to display some textures or shapes, isn't it?
```cpp
sdl::Surface surface = sdl::load_bmp("image.bmp");
// ...
// In your loop:
const sdl::Point point{0, 0};
window.blit(surface, point);
window.update();
```
Note that each instance of `sdl::Window` has its own `sdl::Renderer`, so you don't have to use it directly.
It's also possible to display points or lines:
```cpp
void draw_point(Point const& point);
void draw_points(std::vector<Point> const& points);
void draw_line(Point const& p1, Point const& p2);
```
If you want to display some other stuff (for example, let's imagine a class `Sprite`), you just have to make your custom class inherit from `IDrawable` and implement `on_window`:
```cpp
class Sprite final : public sdl::IDrawable{
public:
  Sprite() = default;
  // ...
private:
  // Inherited from IDrawable
  void on_window(
    sdl::Window& window,
    sdl::Point const& coords,
    NullableRect const& src_rect = sdl::api::NULL_VAL) const override
  {
    // ...
  }
};

// ...
Sprite sprite{};
// ...
window.blit(sprite, sdl::Point{0, 0});
```

### Event handling
This wrapper allows you to handle events without using the basic SDL event system, because it provides a class `sdl::EventHandler` you can use easily:
```cpp
sdl::EventHandler handler;
auto& mouse_handler = handler.get<sdl::MouseStateHandler>();
auto& keyboard_handler = handler.get<sdl::KeyboardStateHandler>();

// You may bind an action to an event:
handler.on_press(sdl::KeyCode::A, [](){
  std::cout << "Key A pressed" << std::endl;
});

// ...

// In your loop:

// Mouse
const auto mouse_state = mouse_handler.state();
const auto mouse_coords = mouse_state.coords();
const auto clicked = mouse_state.clicked(ClickCode::Left);
// Keyboard
const auto keyboard_state = keyboard_handler.state();
const auto key_pressed = keyboard_state[KeyCode::A].pressed;
// ...
handler.update();
```
Note: Don't use `sdl::EventHandler::get<T>()` in your main loop because this operation is very heavy; prefer a reference as in the example.

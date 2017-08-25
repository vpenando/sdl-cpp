#ifndef __SPRITE_H__
#define __SPRITE_H__

// **********************
// ** Standard library **
//***********************
#include <cassert> // assert
#include <chrono>  // std::chrono
#include <utility> // std::pair
#include <vector>  // std::vector

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/noncopyable.h>    // sdl::api::NonCopyable
#include <sdl/api/memory/wrapper.h> // sdl::api::memory::Wrapper, memory::Deleter
#include <sdl/ecs/ecs.h>            // sdl::ecs::Component
#include <sdl/surface.h>            // sdl::Surface
#include "idrawable.h"

namespace sdl {

  class SpriteAnimation final : public ecs::Component {
  public:
    explicit SpriteAnimation(unsigned framerate_ms);
    ~SpriteAnimation();
    void add_frame(SDL_Surface *frame, bool owns = true);
    void update();
    SDL_Surface* current() const;
  private:
    std::chrono::milliseconds framerate_;
    std::chrono::time_point<std::chrono::steady_clock> current_;
    std::vector<std::pair<SDL_Surface *, bool>> frames_;
    unsigned idx_;
  };

  class Sprite final :
    public ecs::Component,
    public IDrawable
  {
  public:
    Sprite();
    void add_animation(SpriteAnimation const& anim);
    void play_animation(unsigned idx);
    void update();
  private:
    void on_window(Window& window, Point const& coords, NullableRect const& src_rect = api::NULL_VAL) const override;
    std::vector<SpriteAnimation> anims_;
    unsigned anim_idx_;
  };
}

#endif // __SPRITE_H__
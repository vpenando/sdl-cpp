#include <sdl/sprite.h>
#include <sdl/window.h>
#include <iostream>

sdl::SpriteAnimation::SpriteAnimation(unsigned framerate_ms)
  : framerate_(framerate_ms), idx_(0)
{
}

sdl::SpriteAnimation::~SpriteAnimation() {
  for (auto const& f : frames_) {
    if (f.first && f.second) {
      SDL_FreeSurface(f.first);
    }
  }
}

void sdl::SpriteAnimation::add_frame(sdl::Surface const& frame, bool owns) {
  assert(frame && "Null pointer");
  frames_.push_back(std::pair<sdl::Surface, bool>(frame, owns));
}

void sdl::SpriteAnimation::update() {
  using Time = std::chrono::high_resolution_clock;
  using ms = std::chrono::milliseconds;
  const auto now = Time::now();
  const auto duration = std::chrono::duration_cast<ms>(now - current_);
  if (duration >= framerate_) {
    current_ = now;
    if (idx_ == frames_.size()) {
      idx_ = 0;
    } else {
      idx_++;
    }
  }
}

sdl::Surface sdl::SpriteAnimation::current() const {
  assert(idx_ < frames_.size() && "Out of bounds");
  assert(frames_[idx_].first && "Null pointer");
  return frames_[idx_].first;
}

sdl::Sprite::Sprite() : anim_idx_(0) {
  
}

void sdl::Sprite::add_animation(SpriteAnimation const& anim) {
  anims_.push_back(anim);
}

void sdl::Sprite::play_animation(unsigned idx) {
  assert(!anims_.empty() && "No animation");
  assert(idx < anims_.size() && "Out of bounds");
  assert(anims_[idx].current() && "Null pointer");
  anim_idx_ = idx;
}

void sdl::Sprite::update() {
  for (auto& a : anims_) {
    a.update();
  }
}

void sdl::Sprite::on_window(Window& window, Point const& coords, NullableRect const& src_rect) const {
  assert(!anims_.empty() && "No animation");
  assert(anim_idx_ < anims_.size() && "Out of bounds");
  assert(anims_[anim_idx_].current() && "Null pointer");
  //window.blit(anims_[anim_idx_].current(), coords, src_rect);
  (void)window;
  (void)coords;
  (void)src_rect;
}
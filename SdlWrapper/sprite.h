#ifndef __SPRITE_H__
#define __SPRITE_H__

// **********************
// ** Standard library **
//***********************
#include <cassert> // assert

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include "ecs.h"         // sdl::ecs::Component
#include "noncopyable.h" // sdl::internal::NonCopyable
#include "wrapper.h"     // sdl::internal::memory::Wrapper, memory::Deleter

namespace sdl{

  class SpriteAnimation;

  class Sprite{
  public:

  };
}

#endif // __SPRITE_H__
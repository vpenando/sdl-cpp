#ifndef __SIZE_H__
#define __SIZE_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include <sdl/ecs/ecs.h> // sdl::ecs::Component

namespace sdl{

  struct Size final : public ecs::Component{
    Size() noexcept : w(0u), h(0u){}
    Size(unsigned width, unsigned height) noexcept : w(width), h(height) {}
    unsigned w, h;
  };

} // namespace sdl

inline bool operator==(sdl::Size const& s1, sdl::Size const& s2) noexcept{
  return s1.w == s2.w;
}

inline bool operator!=(sdl::Size const& s1, sdl::Size const& s2) noexcept{
  return !(s1 == s2);
}

#endif // __SIZE_H__
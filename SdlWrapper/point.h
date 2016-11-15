#ifndef __VECTOR2_H__
#define __VECTOR2_H__

// **********************
// ** Standard library **
//***********************
#include <type_traits> // std::is_arithmetic

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Point

// **********************
// ** Custom lib files **
// **********************
#include "iconvertible.h" // sdl::internal::IConvertible

namespace sdl{
  namespace internal{

    template<class T>
    struct Vector2{
      static_assert(std::is_arithmetic<T>::value, "Invalid type");
      Vector2() noexcept : x(T{}), y(T{}){}
      Vector2(T const& p_x, T const& p_y) noexcept : x(p_x), y(p_y){}
      T x, y;
    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
  } // namespace sdl::internal

  struct Point final :
    public internal::Vector2i,
    public internal::IConvertible<SDL_Point>
  {
    using internal::Vector2i::Vector2i;
    operator SDL_Point() const noexcept override;
  };

} // namespace sdl

#endif // __VECTOR2_H__
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
#include <sdl/api/iconvertible.h> // sdl::api::IConvertible
#include <sdl/ecs/ecs.h>          // sdl::ecs::Component

namespace sdl{
  namespace api{

    template<class T>
    struct Vector2{
      static_assert(std::is_arithmetic<T>::value, "Invalid type");
      Vector2() noexcept : x(T{}), y(T{}){}
      Vector2(T p_x, T p_y) noexcept : x(p_x), y(p_y){}
      T x, y;
    };

    using Vector2i = Vector2<int>;
    using Vector2f = Vector2<float>;
  } // namespace sdl::api

  struct Point final :
    public api::Vector2i,
    public api::IConvertible<SDL_Point>,
    public ecs::Component,
    public Shape
  {
    using api::Vector2i::Vector2i;
    operator SDL_Point() const noexcept override;
  };

} // namespace sdl

template<class T>
inline bool operator==(sdl::api::Vector2<T> const& v1, sdl::api::Vector2<T> const& v2) noexcept{
  return v1.x == v2.x && v1.y == v2.y;
}

template<class T>
inline bool operator!=(sdl::api::Vector2<T> const& v1, sdl::api::Vector2<T> const& v2) noexcept{
  return !(v1 == v2);
}

#endif // __VECTOR2_H__

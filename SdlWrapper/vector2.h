#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <type_traits> // std::is_arithmetic

#include <SDL.h> // SDL_Point

namespace sdl{

  template<class T>
  struct Vector2{
    static_assert(std::is_arithmetic<T>::value, "Invalid type");
    Vector2() noexcept : x(T{}), y(T{}){}
    Vector2(T const& p_x, T const& p_y) noexcept : x(p_x), y(p_y){}
    T x, y;
  };

  using Vector2i = Vector2<int>;
  using Vector2f = Vector2<float>;

  struct Point final : public Vector2i{
    using Vector2i::Vector2i;
    operator SDL_Point() const noexcept{
      SDL_Point point;
      point.x = x;
      point.y = y;
      return point;
    }
  };

} // namespace sdl

#endif // __VECTOR2_H__
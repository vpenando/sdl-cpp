#ifndef __VECTOR2_H__
#define __VECTOR2_H__

namespace sdl{

  template<class T>
  struct Vector2{
    Vector2() : x(T{}), y(T{}){}
    Vector2(T const& p_x, T const& p_y) : x(p_x), y(p_y){}
    T x, y;
  };

  using Vector2i = Vector2<int>;
  using Vector2f = Vector2<float>;

} // namespace sdl

#endif // __VECTOR2_H__
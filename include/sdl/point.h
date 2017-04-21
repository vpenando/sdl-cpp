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

//! @namespace sdl
//! @brief The SDL wrapper main namespace
namespace sdl {
  
  //! @namespace api
  //! @brief The internal SDL API namespace
  namespace api {

    //! @class  Vector2
    //! @brief  Represents a couple of coordinates X and Y
    //! @tparam T The arithmetic type used for X and Y
    template<class T>
    struct Vector2 {
      static_assert(std::is_arithmetic<T>::value, "Invalid type");
      Vector2() noexcept : x(T{}), y(T{}){}
      Vector2(T p_x, T p_y) noexcept : x(p_x), y(p_y) {}
      T x, y;
    };

    //! @typedef Vector2i
    //! @brief   An alias of Vector2<T> with T = int
    //! @see     Vector2
    using Vector2i = Vector2<int>;
    
    //! @typedef Vector2f
    //! @brief   An alias of Vector2<T> with T = float
    //! @see     Vector2
    using Vector2f = Vector2<float>;
    
  } // namespace sdl::api

  //! @class   Point
  //! @brief   The SDL_Point equivalent
  //! @extends Vector2i
  //! @extends IConvertible
  //! @extends Component
  struct Point final :
    public api::Vector2i,
    public api::IConvertible<SDL_Point>,
    public ecs::Component
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

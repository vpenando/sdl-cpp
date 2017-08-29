#ifndef __COLOR_H__
#define __COLOR_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Color, Uint8

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/iconvertible.h> // sdl::api::IConvertible
#include <sdl/ecs/ecs.h>          // sdl::ecs::Component
#include <sdl/types.h>            // sdl::u8, sdl::u32

//! @namespace sdl
//! @brief The SDL wrapper main namespace
namespace sdl {

  //! @class   Color
  //! @brief   Represents a RGBA color
  //! @extends IConvertible
  //! @extends Component
  struct Color final :
    public api::IConvertible<SDL_Color>,
    public ecs::Component
  {
    //! @brief Ctor
    //! @param red   The R value
    //! @param green The G value
    //! @param blue  The B value
    //! @param alpha The A value
    Color(u8 red, u8 green, u8 blue, u8 alpha = 255) noexcept;
    //! @brief Ctor
    //! @param val The hexadecimal representation of a color
    Color(u32 val = 0) noexcept;
    operator SDL_Color() const noexcept override;
    explicit operator u32() const noexcept;
    u8 r, g, b, a;
    const static Color BLACK; //!< The black color template
    const static Color RED;   //!< The red color template
    const static Color GREEN; //!< The green color template
    const static Color BLUE;  //!< The blue color template
  };

} // namespace sdl

inline bool operator==(sdl::Color const& c1, sdl::Color const& c2) noexcept {
  return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;
}

inline bool operator!=(sdl::Color const& c1, sdl::Color const& c2) noexcept {
  return !(c1 == c2);
}

#endif // __COLOR_H__

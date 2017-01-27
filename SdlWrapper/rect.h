#ifndef __RECT_H__
#define __RECT_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL_Rect

// **********************
// ** Custom lib files **
// **********************
#include "ecs.h"          // sdl::ecs::Component
#include "iconvertible.h" // sdl::internal::IConvertible
#include "size.h"         // sdl::Size
#include "point.h"        // sdl::Point

namespace sdl{

  struct Rect final : public internal::IConvertible<SDL_Rect>, public ecs::Component{
    Rect();
    Rect(int coordX, int coordY);
		Rect(int coordX, int coordY, unsigned width, unsigned height);
		Rect(SDL_Rect const& rect);
    operator SDL_Rect() const override;
    //Point pos;
    //Size size;
		int x, y, w, h;
  };

} // namespace sdl

#endif // __RECT_H__
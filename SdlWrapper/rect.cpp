#include "rect.h"

sdl::Rect::Rect()
	: x(0), y(0), w(0), h(0){}

sdl::Rect::Rect(int coordX, int coordY)
	: Rect(coordX, coordY, 0, 0){}

sdl::Rect::Rect(int coordX, int coordY, unsigned width, unsigned height)
	: x(coordX), y(coordY), w(width), h(height){}

sdl::Rect::Rect(SDL_Rect const& rect)
	: Rect(rect.x, rect.y, rect.w, rect.h){}

sdl::Rect::operator SDL_Rect() const{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}
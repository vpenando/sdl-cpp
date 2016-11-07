#ifndef __SIZE_H__
#define __SIZE_H__

namespace sdl{

  struct Size final{
    Size() : w(0u), h(0u){}
    Size(unsigned width, unsigned height) : w(width), h(height){}
    unsigned w, h;
  };

} // namespace sdl

#endif // __SIZE_H__
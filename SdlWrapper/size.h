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
// -

namespace sdl{

  struct Size final{
    Size() noexcept : w(0u), h(0u){}
    Size(unsigned width, unsigned height) noexcept : w(width), h(height){}
    unsigned w, h;
  };

} // namespace sdl

#endif // __SIZE_H__
#ifndef __BASE_H__
#define __BASE_H__

// **********************
// ** Standard library **
//***********************
#include <cassert> // assert

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include "noncopyable.h" // sdl::internal::NonCopyable
#include "wrapper.h"     // sdl::internal::memory::Wrapper, memory::Deleter

namespace sdl{
  namespace internal{

    template<class T, memory::Deleter<T> deleter>
    class Base : public NonCopyable{
    public:
      explicit Base(T* ptr) : wrapper_(ptr){}
      virtual ~Base() = default;
      // For pointer-like use
      operator T*() const noexcept;

    protected:
      memory::Wrapper<T, deleter> wrapper_;
    };

  } // namespace sdl::internal
} // namespace sdl

// Implementation

template<class T, sdl::internal::memory::Deleter<T> deleter>
sdl::internal::Base<T, deleter>::operator T*() const noexcept{
  return wrapper_;
}

#endif // __BASE_H__
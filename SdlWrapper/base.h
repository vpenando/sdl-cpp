#ifndef __BASE_H__
#define __BASE_H__

#include <cassert> // assert

#include "wrapper.h" // memory::Wrapper, memory::Deleter

namespace sdl{
  namespace internal{

    template<class T, memory::Deleter<T> deleter>
    class Base{
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
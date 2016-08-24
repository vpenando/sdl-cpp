#ifndef __BASE_H__
#define __BASE_H__

#include <cassert> // assert

#include "wrapper.h" // memory::Wrapper, memory::Deleter

namespace memory{

  template<class T, Deleter<T> deleter>
  class Base{
  public:
    Base(T* ptr) : wrapper_(ptr){}
    // For pointer-like use
    T* operator->() const noexcept;
    operator T*()   const noexcept;
  protected:
    using value_type = T;
    memory::Wrapper<T, deleter> wrapper_;
  };

} // namespace memory

// Base class for SDL managed resources
template<class T, memory::Deleter<T> deleter>
using SDL_Base = memory::Base<T, deleter>;

// Implementation

template<class T, memory::Deleter<T> deleter>
T* memory::Base<T, deleter>::operator->() const noexcept{
  assert(wrapper_ && "Null pointer");
  return wrapper_;
}

template<class T, memory::Deleter<T> deleter>
memory::Base<T, deleter>::operator T*() const noexcept{
  return wrapper_;
}

#endif // __BASE_H__
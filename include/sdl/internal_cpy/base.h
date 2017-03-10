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
#include <sdl/api/ecs/ecs.h> // sdl::ecs::Component
#include <sdl/api/noncopyable.h> // sdl::api::NonCopyable
#include <sdl/api/memory/wrapper.h>     // sdl::api::memory::Wrapper, memory::Deleter

namespace sdl{
  namespace api{

    template<class T>
    inline void delete_ptr(T *ptr){
      delete ptr;
    }

    template<class T, memory::Deleter<T> deleter = delete_ptr>
    class Base : private NonCopyable, public ecs::Component{
    public:
      explicit Base(T* ptr) : wrapper_(ptr){}
      virtual ~Base() = default;
      // For pointer-like use
      operator T*() const noexcept;

    protected:
      memory::Wrapper<T, deleter> wrapper_;
    };

  } // namespace sdl::api
} // namespace sdl

// Implementation

template<class T, sdl::api::memory::Deleter<T> deleter>
sdl::api::Base<T, deleter>::operator T*() const noexcept{
  return wrapper_;
}

#endif // __BASE_H__
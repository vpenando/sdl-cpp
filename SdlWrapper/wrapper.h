#ifndef __WRAPPER_H__
#define __WRAPPER_H__

// **********************
// ** Standard library **
//***********************
#include <cassert>   // assert
#include <memory>    // std::unique_ptr
#include <stdexcept> // std::runtime_error

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include "noncopyable.h" // sdl::internal::NonCopyable

namespace sdl{
  namespace internal{
    namespace memory{

      // Alias for default pointers deletion
      template<class T>
      using Deleter = void(*)(T*);

      // Raw pointer wrapper (not exactly like std::unique_ptr because of operator T*())
      template<class T, Deleter<T> deleter>
      class Wrapper final : NonCopyable{
      public:
        explicit Wrapper(T* ptr);
        // For pointer-like use
        operator T*() const noexcept; // Converter Wrapper<T> => T*

      private:
        std::unique_ptr<T, Deleter<T>> ptr_;
      };

    } // namespace sdl::internal::memory
  } // namespace sdl::internal
} // namespace sdl

template<class T, sdl::internal::memory::Deleter<T> deleter>
sdl::internal::memory::Wrapper<T, deleter>::Wrapper(T* ptr) : ptr_(ptr, deleter){
  if(!ptr){
    throw std::runtime_error{"Null pointer"};
  }
}

template<class T, sdl::internal::memory::Deleter<T> deleter>
sdl::internal::memory::Wrapper<T, deleter>::operator T*() const noexcept{
  assert(ptr_ && "Null pointer");
  return ptr_.get();
}

#endif // __WRAPPER_H__
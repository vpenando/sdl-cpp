#ifndef __WRAPPER_H__
#define __WRAPPER_H__

#include <cassert> // assert

namespace memory{

  // Alias for default pointers deletion
  template<class T>
  using Deleter = void(*)(T*);

  // Raw pointer wrapper (not exactly like std::unique_ptr because of operator T*())
  template<class T, Deleter<T> deleter>
  class Wrapper final{
  public:
    using value_type = T;
    // Ctor / dtor
    Wrapper(T* ptr);
    ~Wrapper();
    // Deleted member functions
    Wrapper(Wrapper const&) = delete;
    Wrapper& operator=(Wrapper const&) = delete;
    // For pointer-like use
    T* operator->() const noexcept; // Access op
    operator T*()   const noexcept; // Converter Wrapper<T> => T*

  private:
    T* ptr_;
  };

} // namespace memory

template<class T, memory::Deleter<T> deleter>
memory::Wrapper<T, deleter>::Wrapper(T* ptr) : ptr_(ptr){
}

template<class T, memory::Deleter<T> deleter>
memory::Wrapper<T, deleter>::~Wrapper(){
  deleter(ptr_);
}

// Access op
template<class T, memory::Deleter<T> deleter>
T* memory::Wrapper<T, deleter>::operator->() const noexcept{
  return ptr_;
}

template<class T, memory::Deleter<T> deleter>
memory::Wrapper<T, deleter>::operator T*() const noexcept{
  assert(ptr_ && "Null pointer");
  return ptr_;
}

#endif // __WRAPPER_H__
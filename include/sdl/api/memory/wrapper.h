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
#include <sdl/api/noncopyable.h> // sdl::api::NonCopyable

namespace sdl{
	namespace api{
		namespace memory{

			// Alias for default pointers deletion
			template<class T>
			using Deleter = void(*)(T*);

			template<class T>
			using ResourcePtr = std::unique_ptr<T, Deleter<T>>;

      template<class T>
      inline void delete_ptr(T *ptr) {
        delete ptr;
      }

			// Raw pointer wrapper (not exactly like std::unique_ptr because of operator T*())
			template<class T, Deleter<T> deleter = delete_ptr>
			class Wrapper : NonCopyable{
			public:
				explicit Wrapper(T* ptr);
				// For pointer-like use
				operator T*() const noexcept; // Converter Wrapper<T> => T*

			private:
				ResourcePtr<T> ptr_;
			};

		} // namespace sdl::api::memory
	} // namespace sdl::api
} // namespace sdl

template<class T, sdl::api::memory::Deleter<T> deleter>
sdl::api::memory::Wrapper<T, deleter>::Wrapper(T* ptr) : ptr_(ptr, deleter){
	if(!ptr){
		throw std::runtime_error{"Null pointer"};
	}
}

template<class T, sdl::api::memory::Deleter<T> deleter>
sdl::api::memory::Wrapper<T, deleter>::operator T*() const noexcept{
	assert(ptr_ && "Null pointer");
	return ptr_.get();
}

#endif // __WRAPPER_H__
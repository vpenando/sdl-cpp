#ifndef __MATRIX_H__
#define __MATRIX_H__

// **********************
// ** Standard library **
//***********************
#include <algorithm> // std::for_each
#include <cassert>   // assert
#include <vector>    // std::vector

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
// -

namespace sdl {
  namespace api {

    template<class T>
    class Matrix final {
    public:
      // Ctor
      Matrix(unsigned width, unsigned height, T value = T{});
      // Size
      unsigned width() const noexcept;
      unsigned height() const noexcept;
      // Getter / setter
      T& operator()(unsigned x, unsigned y);
      T operator()(unsigned x, unsigned y) const;

    private:
      unsigned width_;
      unsigned height_;
      std::vector<T> buffer_;
    };

    template<class T>
    Matrix<T>::Matrix(unsigned width, unsigned height, T value)
      : width_(width), height_(height), buffer_(width_ * height_)
    {
      assert(height > 0 && "Matrix height can't be null");
      assert(width > 0 && "Matrix width can't be null");
      std::fill(buffer_.begin(), buffer_.end(), value);
    }

    template<class T>
    unsigned Matrix<T>::width() const noexcept {
      return width_;
    }

    template<class T>
    unsigned Matrix<T>::height() const noexcept {
      return height_;
    }

    template<class T>
    T& Matrix<T>::operator()(unsigned x, unsigned y) {
      assert(x < width_ && "Out of bounds");
      assert(y < height_ && "Out of bounds");
      return buffer_[y * width_ + x];
    }

    template<class T>
    T Matrix<T>::operator()(unsigned x, unsigned y) const {
      assert(x < width_ && "Out of bounds");
      assert(y < height_ && "Out of bounds");
      return buffer_[y * width_ + x];
    }

  } // namespace sdl::api
} // namespace sdl

#endif // __MATRIX_H__

#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

// **********************
// ** Standard library **
//***********************
#include <stdexcept> // std::runtime_error

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
// -

namespace sdl{

  class InvalidPathException : public std::runtime_error{
  public:
    InvalidPathException(std::string const& w) : std::runtime_error(w.c_str()){}
  };

}

#endif // __EXCEPTIONS_H__
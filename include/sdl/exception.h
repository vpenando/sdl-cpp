#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <stdexcept> // std::exception
#include <string>    // std::string

namespace sdl {

  class Exception : public std::exception {
  public:
    explicit Exception(std::string const& what);
    virtual ~Exception() = default;
    virtual const char *what() const override;
  private:
    std::string what_;
  };

  class LoadingError : public Exception {
  public:
    using Exception::Exception;
  };

} // namespace sdl

#endif // __EXCEPTION_H__
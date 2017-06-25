#include <sdl/exception.h>

sdl::Exception::Exception(std::string const& what) : what_{what} {
}

const char *sdl::Exception::what() const noexcept {
  return what_.c_str();
}

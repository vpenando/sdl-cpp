#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

namespace sdl{
  namespace internal{

    class noncopyable{
    protected:
      noncopyable() = default;
    private:
      noncopyable(noncopyable const&) = delete;
      noncopyable& operator=(noncopyable const&) = delete;
    };

  } // namespace sdl::internal
} // namespace sdl

#endif // __NONCOPYABLE_H__
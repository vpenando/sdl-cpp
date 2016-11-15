#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

// **********************
// ** Standard library **
//***********************
// -

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
// -

namespace sdl{
  namespace internal{

    class NonCopyable{
    protected:
      NonCopyable() = default;
    private:
      NonCopyable(NonCopyable const&) = delete;
      NonCopyable& operator=(NonCopyable const&) = delete;
    };

  } // namespace sdl::internal
} // namespace sdl

#endif // __NONCOPYABLE_H__
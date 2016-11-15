#ifndef __ICONVERTIBLE_H__
#define __ICONVERTIBLE_H__

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

    template<class T>
    class IConvertible{
    public:
      using value_type = T;
      IConvertible() = default;
      virtual ~IConvertible() = default;
      virtual operator T() const = 0;
    };

  } // namespace sdl::internal
} // namespace sdl

#endif // __ICONVERTIBLE_H__
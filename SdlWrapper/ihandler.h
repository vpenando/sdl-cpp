#ifndef __IHANDLER_H__
#define __IHANDLER_H__

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
#include "ecs.h" // sdl::ecs::Component

namespace sdl{
  namespace internal{

    class Handler{
    public:
      Handler() = default;
      ~Handler() = default;
    };

    template<class T>
    class IHandler : public Handler{
    public:
      IHandler() = default;
      virtual ~IHandler() = default;
      virtual void update() = 0;
      virtual T state() const = 0;
    };

  } // namespace sdl::internal
} // namespace sdl

#endif // __IHANDLER_H__
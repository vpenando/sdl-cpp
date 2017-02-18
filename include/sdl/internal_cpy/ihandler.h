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
#include <sdl/api/ecs/ecs.h> // sdl::ecs::Component

namespace sdl{
  namespace api{

    class Handler{
    public:
      Handler() = default;
      virtual ~Handler() = default;
      virtual void update() = 0;
    };

    template<class T>
    class IHandler : public Handler{
    public:
      using value_type = T;
      IHandler() = default;
      virtual ~IHandler() = default;
      virtual T state() const = 0;
    };

  } // namespace sdl::api
} // namespace sdl

#endif // __IHANDLER_H__
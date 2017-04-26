#ifndef __IUPDATABLE_H__
#define __IUPDATABLE_H__

namespace sdl {
  namespace api {

    class IUpdatable {
    public:
      IUpdatable() = default;
      virtual ~IUpdatable() = default;
      virtual void update() = 0;
    };
    
  } // namespace sdl::api
} // namespace sdl    

#endif // __IUPDATABLE_H__

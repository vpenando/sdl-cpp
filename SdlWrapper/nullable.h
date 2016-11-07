#ifndef __NULLABLE_H__
#define __NULLABLE_H__

namespace sdl{
  namespace internal{

    class null_t final{};
    constexpr null_t NULL_VAL{};

    template<class T>
    class Nullable final{
    public:
      template<class ...Args>
      explicit Nullable(Args... args) : null_(false), value_(args...){}
      Nullable(null_t const&) : null_(true){}
      operator bool() const noexcept{
        return null_;
      }
      T value() const{
        return value_;
      }
    private:
      bool null_;
      T value_;
    };

  } // namespace sdl::internal
} // namespace sdl

#endif // __NULLABLE_H__
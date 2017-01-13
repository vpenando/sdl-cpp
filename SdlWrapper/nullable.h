#ifndef __NULLABLE_H__
#define __NULLABLE_H__

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

    // Null value
    class null_t final{};
    constexpr null_t NULL_VAL{};

    template<class T>
    class Nullable final{
    public:
      using value_type = T;
      Nullable(T const& val) : null_(false), value_(val){}
      template<class ...Args>
      explicit Nullable(Args... args) : null_(false), value_(args...){}
      Nullable(null_t const&) : null_(true){}
      Nullable& operator=(T const& val){
        null_ = false;
        value_ = val;
        return *this;
      }
      Nullable& operator=(null_t const&){
        null_ = true;
        return *this;
      }
      operator bool() const noexcept{
        return !null_;
      }
      T value() const{
        assert(!null_ && "Null value");
        return value_;
      }
    private:
      bool null_;
      T value_;
    };

  } // namespace sdl::internal
} // namespace sdl

#endif // __NULLABLE_H__
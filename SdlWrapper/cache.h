#ifndef __CACHE_H__
#define __CACHE_H_



// **********************
// ** Standard library **
//***********************
#include <array>   // std::array
#include <cassert> // assert

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
// -

template<class T, std::size_t cache_size>
class Cache{
  static_assert(cache_size > 0, "Cache size must be superior than 0");
public:
  using value_type = T;
  Cache();
  Cache(T const& val);
  Cache& operator=(T const& val);
  void reset() noexcept;
  std::size_t size() const noexcept;
  operator bool() const noexcept;
  operator T() const;
  T operator[](std::size_t i) const;

private:
  std::array<T, cache_size> data_;
  std::size_t count_;
};

template<class T, std::size_t cache_size>
Cache<T, cache_size>::Cache() : count_(0){}

template<class T, std::size_t cache_size>
Cache<T, cache_size>::Cache(T const& val) : count_(0){
  *this = val;
}

template<class T, std::size_t cache_size>
Cache<T, cache_size>& Cache<T, cache_size>::operator=(T const& val){
  if(count_ < cache_size - 1){
    count_++;
  }
  for(std::size_t i{count_ - 1}; i > 0; i--){
    data_[i] = data_[i - 1];
  }
  data_[0] = val;
  return *this;
}

template<class T, std::size_t cache_size>
void Cache<T, cache_size>::reset() noexcept{
  count_ = 0;
}

template<class T, std::size_t cache_size>
std::size_t Cache<T, cache_size>::size() const noexcept{
  return count_;
}

template<class T, std::size_t cache_size>
Cache<T, cache_size>::operator bool() const noexcept{
  return count_ > 0;
}

template<class T, std::size_t cache_size>
Cache<T, cache_size>::operator T() const{
  assert(count_ > 0 && "No data");
  return data_[0];
}

template<class T, std::size_t cache_size>
T Cache<T, cache_size>::operator[](std::size_t i) const{
  assert(i < count_ && "Out of bouds");
  return data_[i];
}

#endif // __CACHE_H__
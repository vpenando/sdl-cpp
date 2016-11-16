#ifndef __COMPONENT_H__
#define __COMPONENT_H__

// **********************
// ** Standard library **
//***********************
#include <algorithm>   // std::find_if
#include <cassert>     // assert
#include <functional>  // std::function
#include <memory>      // std::unique_ptr
#include <type_traits> // std::enable_if, std::is_base_of
#include <vector>      // std::vector

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include "noncopyable.h" // sdl::internal::NonCopyable

namespace sdl{
  namespace internal{
    namespace ecs{

  template<class T>
  using UnaryPredicate = std::function<bool(T&)>;

  class Component : NonCopyable{
    template<class T>
    using IS_COMPONENT = std::is_base_of<Component, T>;
    template<class T>
    using ComponentType = typename std::enable_if<IS_COMPONENT<T>::value, T>::type;
  public:
    Component() = default;
    virtual ~Component() = default;

    template<class T, class ...Args>
    ComponentType<T>& add(Args... args);

    template<class T>
    ComponentType<T>& get(UnaryPredicate<T> f = [](auto const&){ return true; });

    template<class T>
    bool contains(UnaryPredicate<T> f = [](auto const&){ return true; }) const;

    template<class T>
    void remove(UnaryPredicate<T> f = [](auto const&){ return true; });

  private:
    std::vector<std::unique_ptr<Component>> components_;
  };

    } // namespace sdl::internal::ecs
  } // namespace sdl::internal
} // namespace sdl

template<class T, class ...Args>
sdl::internal::ecs::Component::ComponentType<T>& sdl::internal::ecs::Component::add(Args... args){
  components_.push_back(std::make_unique<T>(args...));
  assert(components_[components_.size() - 1] && "Null pointer");
  return *static_cast<T*>(components_[components_.size() - 1].get());
}

template<class T>
sdl::internal::ecs::Component::ComponentType<T>& sdl::internal::ecs::Component::get(UnaryPredicate<T> f){
  using ComponentPtr = std::unique_ptr<Component>;
  const auto it = std::find_if(components_.begin(), components_.end(), [&](ComponentPtr const& c){
    const auto ptr = dynamic_cast<T*>(c.get());
    return (ptr != nullptr && f(*ptr));
  });
  assert(it != components_.end() && "Doesn't have this type of component");
  return *dynamic_cast<T*>(it->get());
}

template<class T>
bool sdl::internal::ecs::Component::contains(UnaryPredicate<T> f) const{
  using ComponentPtr = std::unique_ptr<Component>;
  const auto it = std::find_if(components_.begin(), components_.end(), [&](ComponentPtr const& c){
    const auto ptr = dynamic_cast<T*>(c.get());
    return (ptr != nullptr && f(*ptr));
  });
  return it != components_.end();
}

template<class T>
void sdl::internal::ecs::Component::remove(UnaryPredicate<T> f){
  const auto it = std::remove_if(components_.begin(), components_.end(), [](auto const& i){
    const auto ptr = dynamic_cast<T*>(i.get());
    return ptr != nullptr && f(*ptr);
  });
  assert(it != components_.end() && "Doesn't have this type of component");
  components_.erase(it, components_.end());
}

#endif // __COMPONENT_H__
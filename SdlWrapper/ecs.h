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

  class Component{
  public:
    Component() = default;
    virtual ~Component() = default;
  };

  template<class T>
  constexpr static bool is_component(){
    return std::is_base_of<Component, T>::value;
  }

  class BaseComponent : public Component, private NonCopyable{    
    template<class T>
    using ComponentType  = typename std::enable_if<is_component<T>()>::type;
    using ComponentPtr   = std::unique_ptr<Component>;
    using ComponentsList = std::vector<ComponentPtr>;
    using Iterator       = ComponentsList::iterator;
    using ConstIterator  = ComponentsList::const_iterator;
  public:
    BaseComponent() = default;
    virtual ~BaseComponent() = default;

    // Iterators
    Iterator begin();
    ConstIterator begin() const;
    Iterator end();
    ConstIterator end() const;

    // Add a component
    template<class T, class ...Args>
    T& add(Args... args);

    // Get a component
    template<class T>
    ComponentType<T>& get(UnaryPredicate<T> const& f = [](auto const&){ return true; });

    // Check if a component exists
    template<class T>
    bool contains(UnaryPredicate<T> const& f = [](auto const&){ return true; }) const;

    // Remove a component
    template<class T>
    void remove(UnaryPredicate<T> const& f = [](auto const&){ return true; });

  private:
    std::vector<ComponentPtr> components_;
  };

  // ********************
  // ** Implementation **
  // ********************

  inline BaseComponent::Iterator BaseComponent::begin(){
    return components_.begin();
  }

  inline BaseComponent::ConstIterator BaseComponent::begin() const{
    return components_.begin();
  }

  inline BaseComponent::Iterator BaseComponent::end(){
    return components_.end();
  }

  inline BaseComponent::ConstIterator BaseComponent::end() const{
    return components_.end();
  }

  template<class T, class ...Args>
  T& BaseComponent::add(Args... args){
    static_assert(is_component<T>(), "Not a component");
    components_.push_back(std::make_unique<T>(args...));
    assert(components_[components_.size() - 1] && "Null pointer");
    return *static_cast<T*>(components_[components_.size() - 1].get());
  }

  template<class T>
  BaseComponent::ComponentType<T>& BaseComponent::get(UnaryPredicate<T> const& f){
    const auto it = std::find_if(components_.begin(), components_.end(), [&](auto const& c){
      const auto ptr = dynamic_cast<T*>(c.get());
      return (ptr != nullptr && f(*ptr));
    });
    assert(it != components_.end() && "Doesn't have this type of component");
    return *dynamic_cast<T*>(it->get());
  }

  template<class T>
  bool BaseComponent::contains(UnaryPredicate<T> const& f) const{
    static_assert(is_component<T>(), "Not a component");
    const auto it = std::find_if(components_.begin(), components_.end(), [&](auto const& c){
      const auto ptr = dynamic_cast<T*>(c.get());
      return (ptr != nullptr && f(*ptr));
    });
    return it != components_.end();
  }

  template<class T>
  void BaseComponent::remove(UnaryPredicate<T> const& f){
    static_assert(is_component<T>(), "Not a component");
    const auto it = std::remove_if(components_.begin(), components_.end(), [&](auto const& c){
      const auto ptr = dynamic_cast<T*>(c.get());
      return ptr != nullptr && f(*ptr);
    });
    assert(it != components_.end() && "Doesn't have this type of component");
    components_.erase(it, components_.end());
  }

    } // namespace sdl::internal::ecs
  } // namespace sdl::internal
} // namespace sdl


#endif // __COMPONENT_H__
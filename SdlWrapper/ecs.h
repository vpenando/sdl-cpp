#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <algorithm>   // std::find_if
#include <cassert>     // assert
#include <functional>  // std::function
#include <memory>      // std::unique_ptr
#include <type_traits> // std::enable_if, std::is_base_of
#include <vector>      // std::vector

namespace sdl{
  namespace internal{
    namespace ecs{

  class Component{
    template<class T>
    using ComponentType = typename std::enable_if<std::is_base_of<Component, T>::value, T>::type;
  public:
    Component() = default;
    virtual ~Component() = default;

    template<class T, class ...Args>
    ComponentType<T>& add(Args... args){
      components_.push_back(std::make_unique<T>(args...));
      assert(components_[components_.size() - 1] && "Null pointer");
      return *static_cast<T*>(components_[components_.size() - 1].get());
    }

    template<class T>
    ComponentType<T>& get(){
      auto it = std::find_if(components_.begin(), components_.end(), [](auto const& i) -> bool{
        return dynamic_cast<T*>(i.get()) != nullptr;
      });
      assert(it != components_.end() && "Doesn't have this type of component");
      assert(*it && "Null pointer");
      return *static_cast<T*>(it->get());
    }

    template<class T>
    ComponentType<T>& get(std::function<bool(T&)> f){
      const auto it = std::find_if(components_.begin(), components_.end(), [&](std::unique_ptr<Component> const& c){
        const auto ptr = dynamic_cast<T*>(c.get());
        return (ptr != nullptr && f(*ptr));
      });
      assert(it != components_.end() && "Doesn't have this type of component");
      return *dynamic_cast<T*>(it->get());
    }

    template<class T>
    void remove(){
      auto cond = [](auto const& i) -> bool{ return dynamic_cast<T*>(i.get()) != nullptr; };
      auto it = std::remove_if(components_.begin(), components_.end(), cond);
      if(it != components_.end()){
        components_.erase(it, components_.end());
      }
    }

    template<class T>
    void remove(std::function<bool(T&)> f){
      auto cond = [](auto const& i) -> bool{
        const auto ptr = dynamic_cast<T*>(i.get());
        return ptr != nullptr && f(*ptr);
      };
      auto it = std::remove_if(components_.begin(), components_.end(), cond);
      if(it != components_.end()){
        components_.erase(it, components_.end());
      }
    }

  private:
    std::vector<std::unique_ptr<Component>> components_;
  };

    } // namespace sdl::internal::ecs
  } // namespace sdl::internal
} // namespace sdl

#endif // __COMPONENT_H__
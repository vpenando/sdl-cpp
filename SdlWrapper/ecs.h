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
  namespace ecs{

    class Component{
    protected:
      Component() = default;
    public:
      virtual ~Component() = default;
    };

    namespace internal{

      template<class T>
      using UnaryPredicate = std::function<bool(T&)>;
      template<class T>
      struct is_component{
        constexpr static bool value = std::is_base_of<Component, T>::value || std::is_same<T, Component>::value;
      };
    } // namespace sdl::ecs::internal

      // NVI interface
    template<class T>
    class IAttachable{
      static_assert(internal::is_component<T>::value, "Not a component");
    public:
      IAttachable() : ptr_{nullptr}{}
      virtual ~IAttachable() = default;
      void attach_to(T& to);
      void detach() noexcept;
      bool attached() const noexcept;
    private:
      virtual void attach(T& to) = 0;
      T *ptr_;
    };

    template<class T>
    void IAttachable<T>::attach_to(T& to){
      assert(!ptr_ && "Already attached");
      ptr_ = std::addressof(to);
      attach(to);
    }

    template<class T>
    void IAttachable<T>::detach() noexcept{
      assert(ptr_ && "Not attached");
      // Todo - Detach *ptr_
      ptr_ = nullptr;
    }

    template<class T>
    bool IAttachable<T>::attached() const noexcept{
      return ptr_ != nullptr;
    }

    class BaseComponent : public Component{
      using ComponentPtr = std::unique_ptr<Component>;
      using ComponentsList = std::vector<ComponentPtr>;
      using Iterator = ComponentsList::iterator;
      using ConstIterator = ComponentsList::const_iterator;
    public:
      BaseComponent() = default;
      virtual ~BaseComponent() = default;

      // Iterators
      Iterator begin() noexcept;
      ConstIterator begin() const noexcept;
      Iterator end() noexcept;
      ConstIterator end() const noexcept;

      ComponentsList::size_type count() const noexcept;

      // Add a component
      template<class T, class ...Args>
      T& add(Args... args);

      template<class T, class ...Args>
      IAttachable<T>& attach(Args... args);

      // Get a component
      template<class T>
      T& get(internal::UnaryPredicate<T> const& f = [](auto const&){ return true; });

      // Check if a component exists
      template<class T>
      bool contains(internal::UnaryPredicate<T> const& f = [](auto const&){ return true; }) const;

      // Remove a component
      template<class T>
      void remove(internal::UnaryPredicate<T> const& f = [](auto const&){ return true; });

    private:
      std::vector<ComponentPtr> components_;
    };

    // ********************
    // ** Implementation **
    // ********************

    inline BaseComponent::Iterator BaseComponent::begin() noexcept{
      return components_.begin();
    }

    inline BaseComponent::ConstIterator BaseComponent::begin() const noexcept{
      return components_.begin();
    }

    inline BaseComponent::Iterator BaseComponent::end() noexcept{
      return components_.end();
    }

    inline BaseComponent::ConstIterator BaseComponent::end() const noexcept{
      return components_.end();
    }

    inline BaseComponent::ComponentsList::size_type BaseComponent::count() const noexcept{
      return components_.size();
    }

    template<class T, class ...Args>
    T& BaseComponent::add(Args... args){
      static_assert(internal::is_component<T>::value, "Not a component");
      components_.push_back(std::make_unique<T>(args...));
      const auto& component = components_.back();
      assert(component && "Null pointer");
      return *static_cast<T*>(component.get());
    }

    template<class T, class ...Args>
    IAttachable<T>& BaseComponent::attach(Args... args){
      using ThisType = decltype(*this);
      constexpr auto is_this_type = std::is_same<T, ThisType>::value
        || std::is_base_of<ThisType, T>::value;
      static_assert(is_this_type, "Cannot attach this component");
      IAttachable<T>& component = add(args...);
      component.attach_to(*this);
      return component;
    }

    template<class T, class Iterator>
    auto get_iterator(internal::UnaryPredicate<T> const& f, Iterator begin, Iterator end){
      return std::find_if(begin, end, [&](auto const& c){
        const auto ptr = dynamic_cast<T*>(c.get());
        return (ptr != nullptr && f(*ptr));
      });
    }

    template<class T>
    T& BaseComponent::get(internal::UnaryPredicate<T> const& f){
      static_assert(internal::is_component<T>::value, "Not a component");
      /*const auto it = std::find_if(components_.begin(), components_.end(), [&](auto const& c){
      const auto ptr = dynamic_cast<T*>(c.get());
      return (ptr != nullptr && f(*ptr));
      });
      assert(contains(f) && "Doesn't have this type of component");*/
      const auto it = get_iterator(f, components_.begin(), components_.end());
      assert(it != components_.end() && "Doesn't contain this component");
      return *dynamic_cast<T*>(it->get());
    }

    template<class T>
    bool BaseComponent::contains(internal::UnaryPredicate<T> const& f) const{
      static_assert(internal::is_component<T>::value, "Not a component");
      /*const auto it = std::find_if(components_.begin(), components_.end(), [&](auto const& c){
      const auto ptr = dynamic_cast<T*>(c.get());
      return (ptr != nullptr && f(*ptr));
      });*/
      const auto it = get_iterator(f, components_.begin(), components_.end());
      return it != components_.end();
    }

    template<class T>
    void BaseComponent::remove(internal::UnaryPredicate<T> const& f){
      static_assert(internal::is_component<T>::value, "Not a component");
      const auto it = std::remove_if(components_.begin(), components_.end(), [&](auto const& c){
        const auto ptr = dynamic_cast<T*>(c.get());
        return ptr != nullptr && f(*ptr);
      });
      assert(it != components_.end() && "Doesn't have this type of component");
      components_.erase(it, components_.end());
    }

  } // namespace sdl::ecs
} // namespace sdl


#endif // __COMPONENT_H__
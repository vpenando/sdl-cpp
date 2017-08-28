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
#include <sdl/api/noncopyable.h> // sdl::api::NonCopyable

namespace sdl {
  namespace ecs {

    // Basic component class
    class Component {
    protected:
      Component() = default;
    public:
      virtual ~Component() = default;
    };

    namespace api {

      template<class T>
      using UnaryPredicate = std::function<bool(T const&)>;

      template<class T>
      constexpr static bool is_component = std::is_base_of<Component, T>::value || std::is_same<T, Component>::value;

      template<class T, class Iterator>
      auto get_iterator(UnaryPredicate<T> const& f, Iterator begin, Iterator end) {
        return std::find_if(begin, end, [&](auto const& c) {
          const auto ptr = dynamic_cast<T*>(c.get());
          return (ptr != nullptr && f(*ptr));
        });
      }

      // Base component - Can add different component types deriving from ComponentType
      template<class ComponentType>
      class RootComponent
         : public ComponentType,
         private std::vector<std::unique_ptr<ComponentType>>
      {
         using ComponentPtr = typename std::vector<std::unique_ptr<ComponentType>>::value_type;
      public:

         using typename std::vector<std::unique_ptr<ComponentType>>::value_type;
         RootComponent() = default;
         virtual ~RootComponent() = default;

         using std::vector<std::unique_ptr<ComponentType>>::size;
         using std::vector<std::unique_ptr<ComponentType>>::begin;
         using std::vector<std::unique_ptr<ComponentType>>::end;
         

         template<class T, class ...Args>
         T& add(Args&&... args) {
            static_assert(is_component<T>, "Not a component");
            emplace_back(new T(args...));
            const auto& component = back();
            assert(component && "Null pointer");
            return *static_cast<T*>(component.get());
         }

         template<class T>
         T& get(UnaryPredicate<T> const& f = [](const T&) -> bool { return true; }) {
            static_assert(is_component<T>, "Not a component");
            const auto it = get_iterator(f, begin(), end());
            assert(it != end() && "Doesn't contain this component");
            return *dynamic_cast<T*>(it->get());
         }

         template<class T>
         bool contains(UnaryPredicate<T> const& f = [](const T&) -> bool { return true; }) const {
            static_assert(is_component<T>, "Not a component");
            const auto it = get_iterator(f, begin(), end());
            return it != end();
         }

         template<class T>
         void remove(UnaryPredicate<T> const& f = [](const T&) -> bool { return true; }) {
            static_assert(is_component<T>, "Not a component");
            const auto it = std::remove_if(begin(), end(), [&](auto const& c) {
               const auto ptr = dynamic_cast<T*>(c.get());
               return ptr != nullptr && f(*ptr);
            });
            assert(it != end() && "Doesn't have this type of component");
            erase(it, end());
         }

      private:
         using std::vector<std::unique_ptr<ComponentType>>::emplace_back;
         using std::vector<std::unique_ptr<ComponentType>>::back;
         using std::vector<std::unique_ptr<ComponentType>>::erase;
      };

    } // namespace sdl::ecs::api
     
    // Specialization
    using BaseComponent = api::RootComponent<Component>;

  } // namespace sdl::ecs
} // namespace sdl

#endif // __COMPONENT_H__

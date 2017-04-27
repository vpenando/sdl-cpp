#ifndef __BOXCOLLIDER_H__
#define __BOXCOLLIDER_H__

// **********************
// ** Standard library **
//***********************
#include <algorithm> // std::find_if
#include <array>     // std::array

// **********************
// ** SDL header files **
// **********************
// -

// **********************
// ** Custom lib files **
// **********************
#include <sdl/point.h> // sdl::Point
#include <sdl/rect.h>  // sdl::Rect
#include <sdl/size.h>  // sdl::Size

namespace sdl {

  using BoxColliderPointsArray = std::array<Point, 4>;

  class BoxCollider final {
  public:
    BoxCollider(int x, int y, unsigned w, unsigned h) : rect_(x, y, w, h) {}
    BoxCollider(Rect const& rect) : rect_(rect) {}
    Rect rect() const;
    bool collides(Point const& point) const;
    bool collides(BoxCollider const& other) const;
  private:
    BoxColliderPointsArray collider_array() const;
    Rect rect_;
  };

  Rect BoxCollider::rect() const {
    return rect_;
  }

  bool BoxCollider::collides(Point const& point) const {
    return (point.x >= rect_.x && point.x < static_cast<int>(rect_.x + rect_.w)
         && point.y >= rect_.y && point.y < static_cast<int>(rect_.y + rect_.h));
  }

  bool BoxCollider::collides(BoxCollider const& other) const {
    const auto points = other.collider_array();
    const auto it = std::find_if(points.begin(), points.end(), [&](auto const& p) -> bool {
      return collides(p);
    });
    return it != points.end();
  }

  BoxColliderPointsArray BoxCollider::collider_array() const {
    return BoxColliderPointsArray {
      Point{ rect_.x, rect_.y },
      Point{ rect_.x + static_cast<int>(rect_.w), rect_.y },
      Point{ rect_.x, rect_.y + static_cast<int>(rect_.h) },
      Point{ rect_.x + static_cast<int>(rect_.w), rect_.y + static_cast<int>(rect_.h) }
    };
  }

  inline bool collision(BoxCollider const& c1, BoxCollider const& c2) {
    return c1.collides(c2) || c2.collides(c1);
  }

  class RelativeBoxCollider final {
  public:
    RelativeBoxCollider(int& x, int& y, unsigned w, unsigned h) : x_(x), y_(y), size_(w, h) {}
    Rect rect() const { return Rect{x_, y_, size_.w, size_.h}; }
    operator BoxCollider() const {
      return BoxCollider{x_, y_, size_.w, size_.h};
    }
    bool collides(Point const& point) const {
      const auto collider = static_cast<BoxCollider>(*this);
      return collider.collides(point);
    }
    bool collides(BoxCollider const& other) const {
      const auto collider = static_cast<BoxCollider>(*this);
      return collider.collides(other);
    }
  private:
    int& x_;
    int& y_;
    Size size_;
  };
  
} // namespace sdl

#endif // __BOXCOLLIDER_H__

#ifndef __KEYS_H__
#define __KEYS_H__

// **********************
// ** Standard library **
//***********************
#include <vector> // std::vector

// **********************
// ** SDL header files **
// **********************
#include <SDL.h> // SDL keys

// **********************
// ** Custom lib files **
// **********************
#include <sdl/api/ihandler.h> // sdl::api::IHandler
#include <sdl/ecs/ecs.h>      // sdl::ecs::Component

namespace sdl {

  enum class KeyCode {
    A = SDLK_a,
    B = SDLK_b,
    C = SDLK_c,
    D = SDLK_d,
    E = SDLK_e,
    F = SDLK_f,
    G = SDLK_g,
    H = SDLK_h,
    I = SDLK_i,
    J = SDLK_j,
    K = SDLK_k,
    L = SDLK_l,
    M = SDLK_m,
    N = SDLK_n,
    O = SDLK_o,
    P = SDLK_p,
    Q = SDLK_q,
    R = SDLK_r,
    S = SDLK_s,
    T = SDLK_t,
    U = SDLK_u,
    V = SDLK_v,
    W = SDLK_w,
    X = SDLK_x,
    Y = SDLK_y,
    Z = SDLK_z,
    // Numbers
    Num0 = SDLK_0,
    Num1 = SDLK_1,
    Num2 = SDLK_2,
    Num3 = SDLK_3,
    Num4 = SDLK_4,
    Num5 = SDLK_5,
    Num6 = SDLK_6,
    Num7 = SDLK_7,
    Num8 = SDLK_8,
    Num9 = SDLK_9,
    // Others
    Ctrl = SDLK_LCTRL | SDLK_RCTRL,
    LeftCtrl = SDLK_LCTRL,
    RightCtrl = SDLK_RCTRL,
    Enter = SDLK_RETURN | SDLK_KP_ENTER,
    Return = SDLK_RETURN,
    Alt = SDLK_ALTERASE,
    Shift = SDLK_LSHIFT | SDLK_RSHIFT,
    LeftShift = SDLK_LSHIFT,
    RightShift = SDLK_RSHIFT,
    Tab = SDLK_TAB | SDLK_KP_TAB,
    Esc = SDLK_ESCAPE
  };

  struct Key final {
    Key(KeyCode c, bool p) : code(c), pressed(p) {}
    KeyCode code;
    bool pressed;
  };

  class KeyboardState final {
  public:
    KeyboardState(std::vector<Uint8> const& state);
    Key operator[](KeyCode code) const;
    Key operator[](SDL_Keycode code) const;
  private:
    std::vector<Uint8> state_;
  };

  class KeyboardStateHandler final :
    public api::IHandler<KeyboardState>,
    public ecs::Component {
  public:
    KeyboardStateHandler(bool read_events = false);
    KeyboardState state() const override;
    void update() override;
  private:
    bool read_events_;
    std::vector<Uint8> state_;
  };

} // namespace sdl

#endif // __KEYS_H__
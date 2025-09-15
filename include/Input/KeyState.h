#pragma once

#include "Keys.h"

namespace input {
struct KeyState {
  KeyState(KEY key) : key(key) {}
  KEY key;
  bool pressed = false;
};

} // namespace input

#pragma once

#include "KeyState.h"
#include <unordered_map>

namespace input {
class KeyManager {
public:
  KeyManager();

  void PressKey(KEY key);
  void ReleaseKey(KEY key);
  bool IsKeyPressed(KEY key) const;

private:
  std::unordered_map<KEY, KeyState> mKeysState;
};
} // namespace input

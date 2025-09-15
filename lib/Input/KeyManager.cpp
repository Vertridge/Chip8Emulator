#include "Input/KeyManager.h"

namespace input {
KeyManager::KeyManager() {
  for (int i = 0x1; i <= 0xF; ++i) {
    KEY key = static_cast<KEY>(i);
    mKeysState.emplace(key, KeyState(key));
  }
}

void KeyManager::PressKey(KEY key) { mKeysState.at(key).pressed = true; }
void KeyManager::ReleaseKey(KEY key) { mKeysState.at(key).pressed = false; }
bool KeyManager::IsKeyPressed(KEY key) const {
  return mKeysState.at(key).pressed;
}
} // namespace input

#include "catch.hpp"

#include "Input/KeyManager.h"

TEST_CASE("KeyState") {
  input::KeyManager manager;

  SECTION("Press Key") {
    for (int i = 0x1; i <= 0xF; ++i) {
      manager.PressKey(static_cast<input::KEY>(i));
      CHECK(manager.IsKeyPressed(static_cast<input::KEY>(i)));
    }
  }

  SECTION("Release Key") {
    for (int i = 0x1; i <= 0xF; ++i) {
      manager.ReleaseKey(static_cast<input::KEY>(i));
      CHECK_FALSE(manager.IsKeyPressed(static_cast<input::KEY>(i)));
    }
  }
}

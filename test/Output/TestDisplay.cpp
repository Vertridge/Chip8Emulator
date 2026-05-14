#include "catch.hpp"

#include "Output/Display.h"
#include <vector>

using namespace Output;

TEST_CASE("Drawing") {
  Display display;

  std::vector<std::uint8_t> sprite = {0xF, 0XF, 0XF};
  display.Draw(0, 0, sprite);
  for (auto i = 0U; i < sprite.size(); ++i) {
    CHECK(display.GetScreen()[i] == sprite[i]);
  }
}

TEST_CASE("Clearing") {
  Display display;
  display.Draw(0, 0, {0xF, 0XF, 0XF});
  CHECK(display.GetScreen()[0] == 0xF);
  display.Clear();
  CHECK(display.GetScreen()[0] == 0x0);
}

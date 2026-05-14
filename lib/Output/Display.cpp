#include "Output/Display.h"

#include <iostream>

namespace Output {
Display::Display() { mScreen.resize(display_width * display_height, 0U); }

void Display::Draw(std::size_t x, std::size_t y,
                   std::vector<std::uint8_t> data) {
  std::cout << "Drawing to screen\n";
  for (auto i = 0U; i < data.size(); ++i) {
    mScreen[x * display_width + y + i] = data[i];
  }
}

void Display::Clear() { std::fill(mScreen.begin(), mScreen.end(), 0); }

} // namespace Output

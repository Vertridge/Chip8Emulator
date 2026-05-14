#include "Output/Display.h"

#include <iostream>

namespace Output {
Display::Display() { mScreen.resize(display_width * display_width, 0U); }

void Display::Draw(std::size_t x, std::size_t y,
                   std::vector<std::uint8_t> data) {
  std::cout << "Drawing to screen\n";
}

void Display::Clear() { std::fill(mScreen.begin(), mScreen.end(), 0); }

} // namespace Output

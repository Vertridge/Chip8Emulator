#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
namespace Output {

constexpr std::size_t display_width = 128;
constexpr std::size_t display_height = 64;

class Display {
public:
  Display();

  void Draw(std::size_t x, std::size_t y, std::vector<std::uint8_t> data);
  void Clear();
  const std::vector<std::uint8_t> &GetScreen() { return mScreen; }

private:
  std::vector<std::uint8_t> mScreen;
};
} // namespace Output

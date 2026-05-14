#pragma once

#include <array>
#include <cassert>
#include <cstdint>

namespace Output::Sprites {
constexpr std::uint16_t sprite_size = 5;
using Sprite = std::array<std::uint8_t, 5>;

constexpr Sprite sprite_0 = {0xF0, 0x90, 0x90, 0x90, 0xF0};
constexpr Sprite sprite_1 = {0x20, 0x60, 0x20, 0x20, 0x70};
constexpr Sprite sprite_2 = {0xF0, 0x10, 0xF0, 0x80, 0xF0};
constexpr Sprite sprite_3 = {0xF0, 0x10, 0xF0, 0x10, 0xF0};
constexpr Sprite sprite_4 = {0x90, 0x90, 0xF0, 0x10, 0x10};
constexpr Sprite sprite_5 = {0xF0, 0x80, 0xF0, 0x10, 0xF0};
constexpr Sprite sprite_6 = {0xF0, 0x80, 0xF0, 0x90, 0xF0};
constexpr Sprite sprite_7 = {0xF0, 0x10, 0x20, 0x40, 0x40};
constexpr Sprite sprite_8 = {0xF0, 0x90, 0xF0, 0x90, 0xF0};
constexpr Sprite sprite_9 = {0xF0, 0x90, 0xF0, 0x10, 0xF0};
constexpr Sprite sprite_A = {0xF0, 0x90, 0xF0, 0x90, 0x90};
constexpr Sprite sprite_B = {0xE0, 0x90, 0xE0, 0x90, 0xE0};
constexpr Sprite sprite_C = {0xF0, 0x80, 0x80, 0x80, 0xF0};
constexpr Sprite sprite_D = {0xE0, 0x90, 0x90, 0x90, 0xE0};
constexpr Sprite sprite_E = {0xF0, 0x80, 0xF0, 0x80, 0xF0};
constexpr Sprite sprite_F = {0xF0, 0x80, 0xF0, 0x80, 0x80};

constexpr std::uint16_t sprite_0_address = 0;
constexpr std::uint16_t sprite_1_address = sprite_0_address + sprite_size;
constexpr std::uint16_t sprite_2_address = sprite_1_address + sprite_size;
constexpr std::uint16_t sprite_3_address = sprite_2_address + sprite_size;
constexpr std::uint16_t sprite_4_address = sprite_3_address + sprite_size;
constexpr std::uint16_t sprite_5_address = sprite_4_address + sprite_size;
constexpr std::uint16_t sprite_6_address = sprite_5_address + sprite_size;
constexpr std::uint16_t sprite_7_address = sprite_6_address + sprite_size;
constexpr std::uint16_t sprite_8_address = sprite_7_address + sprite_size;
constexpr std::uint16_t sprite_9_address = sprite_8_address + sprite_size;
constexpr std::uint16_t sprite_A_address = sprite_9_address + sprite_size;
constexpr std::uint16_t sprite_B_address = sprite_A_address + sprite_size;
constexpr std::uint16_t sprite_C_address = sprite_B_address + sprite_size;
constexpr std::uint16_t sprite_D_address = sprite_C_address + sprite_size;
constexpr std::uint16_t sprite_E_address = sprite_D_address + sprite_size;
constexpr std::uint16_t sprite_F_address = sprite_E_address + sprite_size;

inline std::uint16_t GetSpriteAddress(std::uint8_t value) {
  switch (value) {
  case 0x0:
    return sprite_0_address;
  case 0x1:
    return sprite_1_address;
  case 0x2:
    return sprite_2_address;
  case 0x3:
    return sprite_3_address;
  case 0x4:
    return sprite_4_address;
  case 0x5:
    return sprite_5_address;
  case 0x6:
    return sprite_6_address;
  case 0x7:
    return sprite_7_address;
  case 0x8:
    return sprite_8_address;
  case 0x9:
    return sprite_9_address;
  case 0xA:
    return sprite_A_address;
  case 0xB:
    return sprite_B_address;
  case 0xC:
    return sprite_C_address;
  case 0xD:
    return sprite_D_address;
  case 0xE:
    return sprite_E_address;
  case 0xF:
    return sprite_F_address;
  }
  assert(false);
  return 0;
}
} // namespace Output::Sprites

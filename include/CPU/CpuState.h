#pragma once

#include <cstdint>
namespace cpu {

using registertype = std::uint8_t;
using addressregistertype = std::uint16_t;

enum class Register {
  // General purpose registers.
  V0 = 0,
  V1,
  V2,
  V3,
  V4,
  V5,
  V6,
  V7,
  V8,
  V9,
  VA,
  VB,
  VC,
  VD,
  VE,
  // Used for flags by some instructions.
  VF,
  // 16bit register to store 12bit address.
  I = 0xFF,

  // Special purpose registers for delay and sound timers.
  VDelay = 0xFFA,
  VSound = 0xFFB,

  // 16bit register to keep track of the program counter.
  PC = 0xFFF0,
  // 8bit points to the topmost level of the stack.
  SP = 0xFFF1,
};

} // namespace cpu

#pragma once

#include "Memory.h"

// stdlib

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

struct CpuState {
  struct registers {
    std::uint8_t V0 = 0;
    std::uint8_t V1 = 0;
    std::uint8_t V2 = 0;
    std::uint8_t V3 = 0;
    std::uint8_t V4 = 0;
    std::uint8_t V5 = 0;
    std::uint8_t V6 = 0;
    std::uint8_t V7 = 0;
    std::uint8_t V8 = 0;
    std::uint8_t V9 = 0;
    std::uint8_t VA = 0;
    std::uint8_t VB = 0;
    std::uint8_t VC = 0;
    std::uint8_t VD = 0;
    std::uint8_t VE = 0;
    std::uint8_t VF = 0;
    std::uint16_t I = 0;
    std::uint8_t VDelay = 0;
    std::uint8_t VSound = 0;
    std::uint16_t PC = 0;
    std::uint8_t SP = 0;
  } registers;

  Memory memory;
};

} // namespace cpu

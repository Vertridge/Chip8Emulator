#pragma once

#include "CpuState.h"

#include <cstdint>
#include <string>

namespace cpu {
std::string ToString(Register reg);
std::uint8_t &GetRegister(Register reg, CpuState &state);
} // namespace cpu

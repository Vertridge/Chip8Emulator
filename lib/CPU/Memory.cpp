#include "CPU/Memory.h"

// stdlib
#include <cassert>
#include <cstdint>

namespace cpu {
Memory::Memory() { mMemoryBuffer.resize(memory_size, 0U); }

std::uint8_t Memory::Read(std::uint16_t address) const {
  assert(IsValidAddress(address) && "Don't read outside the buffer");
  return mMemoryBuffer[address];
}

void Memory::Write(std::uint16_t address, std::uint8_t value) {
  assert(IsValidAddress(address) && "Don't read outside the buffer");
  mMemoryBuffer[address] = value;
}

bool Memory::IsValidAddress(std::uint16_t address) const {
  return address < mMemoryBuffer.size() && address >= memory_start;
}

} // namespace cpu

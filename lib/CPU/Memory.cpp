#include "CPU/Memory.h"

// stdlib
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>

namespace cpu {
Memory::Memory() { mMemoryBuffer.resize(memory_size, 0U); }

std::uint8_t Memory::Read(std::uint16_t address) const {
  assert(IsValidAddress(address) && "Don't read outside the buffer");
  return mMemoryBuffer[address];
}

std::uint16_t Memory::ReadUint16(std::uint16_t address) const {
  std::uint8_t high = Read(address);
  std::uint8_t low = Read(address + 1);
  uint16_t result = (static_cast<uint16_t>(high) << 8) | low;
  return result;
}

void Memory::Write(std::uint16_t address, std::uint8_t value) {
  assert(IsValidAddress(address) && "Don't read outside the buffer");
  mMemoryBuffer[address] = value;
}

bool Memory::IsValidAddress(std::uint16_t address) const {
  return address < mMemoryBuffer.size() && address >= memory_start;
}

bool Memory::LoadIntoMemory(std::vector<std::uint8_t> buffer,
                            std::uint16_t address) {
  if (!IsValidAddress(address)) {
    return false;
  }
  if (!IsValidAddress(address + buffer.size())) {
    return false;
  }
  std::copy(buffer.begin(), buffer.end(), mMemoryBuffer.begin() + address);
  return true;
}

void Memory::Dump(std::ostream &os) {
  os << "Dumpiong Memory Buffer size: " << mMemoryBuffer.size() << std::endl;
  for (const auto &byte : mMemoryBuffer) {
    os << std::hex << (std::uint32_t)byte << " ";
  }
  os << std::endl;
}

} // namespace cpu

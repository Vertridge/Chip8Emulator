#pragma once

// stdlib
#include <cstdint>
#include <vector>

namespace cpu {

constexpr auto memory_size = 0x1000U;
// The first 512 bytes, from 0x000 to 0x1FF, are where the original interpreter
// was located, and should not be used by programs
constexpr auto memory_start = 0x200U;

class Memory {
public:
  Memory();
  Memory(Memory &) = delete;
  Memory(Memory &&) = delete;
  Memory &operator=(const Memory &) = delete;

  std::uint8_t Read(std::uint16_t address) const;
  void Write(std::uint16_t address, std::uint8_t value);
  bool IsValidAddress(std::uint16_t address) const;

private:
  std::vector<std::uint8_t> mMemoryBuffer;
};

} // namespace cpu

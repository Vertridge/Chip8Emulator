#pragma once

// stdlib
#include <cstdint>
#include <ostream>
#include <vector>

namespace cpu {

constexpr auto memory_size = 0x1000U;
// The first 512 bytes, from 0x000 to 0x1FF, are where the original interpreter
// was located, and should not be used by programs
constexpr auto memory_start = 0x200U;
constexpr auto instruction_start = 0x200U;

class Memory {
public:
  Memory();
  Memory(Memory &) = delete;
  Memory(Memory &&) = delete;
  Memory &operator=(const Memory &) = delete;

  std::uint8_t Read(std::uint16_t address) const;
  std::uint16_t ReadUint16(std::uint16_t address) const;
  void Write(std::uint16_t address, std::uint8_t value);
  void WriteUint16(std::uint16_t address, std::uint16_t value);
  bool IsValidAddress(std::uint16_t address) const;
  bool LoadIntoMemory(std::vector<std::uint8_t> buffer, std::uint16_t address);
  void Dump(std::ostream &os);

  void PushStack(std::uint16_t value, std::uint8_t stackPointer);
  std::uint16_t PopStack(std::uint8_t stackPointer);

private:
  std::vector<std::uint8_t> mMemoryBuffer;
  std::vector<std::uint16_t> mStack;
};

} // namespace cpu

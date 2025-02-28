#pragma once

#include <array>
#include <cstdint>
#include <exception>
#include <ostream>
#include <string>
#include <string_view>
#include <vector>

namespace Instructions {

enum class Opcode {
  CLS,
  RET,
  SYS,
  JP,
  RND,
  CALL,
  SE,
  SNE,
  LD,
  ADD,
  OR,
  AND,
  XOR,
  SUB,
  SHR,
  SUBN,
  SHL,
  SKP,
  SKNP,
  DRW,
  // Super chip-48 instructions
  SCD,
  SCR,
  SCL,
  EXIT,
  LOW,
  HIGH
};

class Instruction {
public:
  Instruction(Opcode opcode, std::uint8_t address, std::uint16_t data);
  Opcode GetOpcode() { return mOpcode; }
  std::uint8_t GetAddress() { return mAddress; }

  virtual void Dump(std::ostream &os);
  virtual void Execute();

protected:
  std::uint8_t mAddress;
  std::uint16_t mData;

private:
  Opcode mOpcode;
};

class SysInstruction : public Instruction {
public:
  SysInstruction(std::uint8_t address, std::uint16_t data);

  std::uint8_t GetExecAddr() { return mExecAddr; }
  void Dump(std::ostream &os);
  void Execute();

private:
  std::uint16_t mExecAddr;
};

} // namespace Instructions

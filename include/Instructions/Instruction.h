#pragma once

#include <CPU/CpuState.h>

#include <cstdint>
#include <ostream>
#include <string>
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

class ClsInstruction : public Instruction {
public:
  ClsInstruction(std::uint8_t address, std::uint16_t data);
  void Execute();
};

class RetInstruction : public Instruction {
public:
  RetInstruction(std::uint8_t address, std::uint16_t data);
  void Execute();
};

class JpInstruction : public Instruction {
public:
  JpInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetExecAddr() { return mExecAddr; }
  void Dump(std::ostream &os);
  void Execute();

private:
  std::uint16_t mExecAddr;
};

class AddInstruction : public Instruction {
public:
  AddInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetConstant() { return mConstant; }
  cpu::Register GetRegister() { return mRegister; }
  void Dump(std::ostream &os);
  void Execute();

private:
  cpu::Register mRegister;
  std::uint8_t mConstant;
};

} // namespace Instructions

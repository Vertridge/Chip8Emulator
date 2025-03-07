#pragma once

#include <CPU/CpuState.h>

#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

using namespace cpu;

namespace Instructions {

enum class Opcode {
  CLS,
  RET,
  SYS,
  JP,
  RND,
  CALL,
  SExkk,
  SExy,
  SNExkk,
  SNExy,
  LDxkk,
  LDxy,
  LDnnn,
  LDxdt,
  LDx0,
  LDdtx,
  LDstx,
  LDfx,
  LDbx,
  LDix,
  LDxi,
  ADDxkk,
  ADDxy,
  ADDix,
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
  virtual void Execute(CpuState &state);

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
  void Execute(CpuState &state);

private:
  std::uint16_t mExecAddr;
};

class ClsInstruction : public Instruction {
public:
  ClsInstruction(std::uint8_t address, std::uint16_t data);
  void Execute(CpuState &state);
};

class RetInstruction : public Instruction {
public:
  RetInstruction(std::uint8_t address, std::uint16_t data);
  void Execute(CpuState &state);
};

class JpInstruction : public Instruction {
public:
  JpInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetExecAddr() { return mExecAddr; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  std::uint16_t mExecAddr;
};

class CallInstruction : public Instruction {
public:
  CallInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetExecAddr() { return mExecAddr; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  std::uint16_t mExecAddr;
};

/// If the the content of register Vx is equal to contant kk, skip the next
/// instruction.
class SexkkInstruction : public Instruction {
public:
  SexkkInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetConstant() { return mConstant; }
  Register GetRegister() { return mRegister; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegister;
  std::uint8_t mConstant;
};

/// If the the content of register Vx is equal to register Cy, skip the next
/// instruction.
class SexyInstruction : public Instruction {
public:
  SexyInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

/// If the the content of register Vx is not equal to contant kk, skip the next
/// instruction.
class SnexkkInstruction : public Instruction {
public:
  SnexkkInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetConstant() { return mConstant; }
  Register GetRegister() { return mRegister; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegister;
  std::uint8_t mConstant;
};

/// If the the content of register Vx is not equal to register Vy, skip the next
/// instruction.
class SnexyInstruction : public Instruction {
public:
  SnexyInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class LdxkkInstruction : public Instruction {
public:
  LdxkkInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetConstant() { return mConstant; }
  Register GetRegister() { return mRegister; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegister;
  std::uint8_t mConstant;
};

class LdxyInstruction : public Instruction {
public:
  LdxyInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class AddxkkInstruction : public Instruction {
public:
  AddxkkInstruction(std::uint8_t address, std::uint16_t data);
  std::uint8_t GetConstant() { return mConstant; }
  Register GetRegister() { return mRegister; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegister;
  std::uint8_t mConstant;
};

class AddxyInstruction : public Instruction {
public:
  AddxyInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class SubInstruction : public Instruction {
public:
  SubInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class SubnInstruction : public Instruction {
public:
  SubnInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class OrInstruction : public Instruction {
public:
  OrInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class AndInstruction : public Instruction {
public:
  AndInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class XorInstruction : public Instruction {
public:
  XorInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class ShrInstruction : public Instruction {
public:
  ShrInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class ShlInstruction : public Instruction {
public:
  ShlInstruction(std::uint8_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

} // namespace Instructions

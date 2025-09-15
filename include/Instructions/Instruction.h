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
  Instruction(Opcode opcode, std::uint16_t address, std::uint16_t data);
  Opcode GetOpcode() { return mOpcode; }
  std::uint16_t GetAddress() { return mAddress; }

  virtual void Dump(std::ostream &os);
  virtual void Execute(CpuState &state);
  virtual ~Instruction() = default;

protected:
  std::uint16_t mAddress;
  std::uint16_t mData;

private:
  Opcode mOpcode;
};

class SysInstruction : public Instruction {
public:
  SysInstruction(std::uint16_t address, std::uint16_t data);

  std::uint8_t GetExecAddr() { return mExecAddr; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  std::uint16_t mExecAddr;
};

class ClsInstruction : public Instruction {
public:
  ClsInstruction(std::uint16_t address, std::uint16_t data);
  void Execute(CpuState &state);
};

class RetInstruction : public Instruction {
public:
  RetInstruction(std::uint16_t address, std::uint16_t data);
  void Execute(CpuState &state);
};

class JpInstruction : public Instruction {
public:
  JpInstruction(std::uint16_t address, std::uint16_t data);
  std::uint8_t GetExecAddr() { return mExecAddr; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  std::uint16_t mExecAddr;
};

class CallInstruction : public Instruction {
public:
  CallInstruction(std::uint16_t address, std::uint16_t data);
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
  SexkkInstruction(std::uint16_t address, std::uint16_t data);
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
  SexyInstruction(std::uint16_t address, std::uint16_t data);
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
  SnexkkInstruction(std::uint16_t address, std::uint16_t data);
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
  SnexyInstruction(std::uint16_t address, std::uint16_t data);
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
  LdxkkInstruction(std::uint16_t address, std::uint16_t data);
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
  LdxyInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

/// Sets register I to value nnn.
class LdnnnInstruction : public Instruction {
public:
  LdnnnInstruction(std::uint16_t address, std::uint16_t data);
  std::uint16_t GetValue() { return mValue; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  std::uint16_t mValue;
};

/// Set register x to value of delay timer register
class LdxdtInstruction : public Instruction {
public:
  LdxdtInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
};

/// Set value of delay timer register equal to register x
class LddtxInstruction : public Instruction {
public:
  LddtxInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
};

/// Set value of sound timer register equal to register x
class LdstxInstruction : public Instruction {
public:
  LdstxInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
};

class LdixInstruction : public Instruction {
public:
  LdixInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
};

class LdxiInstruction : public Instruction {
public:
  LdxiInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
};

class AddxkkInstruction : public Instruction {
public:
  AddxkkInstruction(std::uint16_t address, std::uint16_t data);
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
  AddxyInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

class AddixInstruction : public Instruction {
public:
  AddixInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
};

class SubInstruction : public Instruction {
public:
  SubInstruction(std::uint16_t address, std::uint16_t data);
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
  SubnInstruction(std::uint16_t address, std::uint16_t data);
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
  OrInstruction(std::uint16_t address, std::uint16_t data);
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
  AndInstruction(std::uint16_t address, std::uint16_t data);
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
  XorInstruction(std::uint16_t address, std::uint16_t data);
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
  ShrInstruction(std::uint16_t address, std::uint16_t data);
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
  ShlInstruction(std::uint16_t address, std::uint16_t data);
  Register GetRegisterX() { return mRegisterX; }
  Register GetRegisterY() { return mRegisterY; }
  void Dump(std::ostream &os);
  void Execute(CpuState &state);

private:
  Register mRegisterX;
  Register mRegisterY;
};

} // namespace Instructions

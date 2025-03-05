#include "Instructions/InstructionUtil.h"
#include <Instructions/Instruction.h>

#include <CPU/CpuUtil.h>

#include <cassert>
#include <ios>

using namespace cpu;

namespace Instructions {

namespace {
constexpr std::uint16_t addr12bit_mask = 0x0FFF;
constexpr std::uint16_t regx_mask = 0x0F00;
constexpr std::uint16_t regy_mask = 0x00F0;
constexpr std::uint16_t const_mask = 0x00FF;
} // namespace

Instruction::Instruction(Opcode opcode, std::uint8_t address,
                         std::uint16_t data)
    : mAddress(address), mData(data), mOpcode(opcode) {}

void Instruction::Dump(std::ostream &os) {
  os << "0x" << std::hex << (std::uint16_t)mAddress << " " << ToString(mOpcode);
}

void Instruction::Execute(CpuState & /*state*/) {
  assert(false && "Instruction not implemented");
}

SysInstruction::SysInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::SYS, address, data) {
  mExecAddr = data & addr12bit_mask;
}

void SysInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " 0x" << std::hex << mExecAddr;
}

void SysInstruction::Execute(CpuState & /*state*/) {
  assert(false && "Instruction not implemented");
}

ClsInstruction::ClsInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::CLS, address, data) {}

void ClsInstruction::Execute(CpuState & /*state*/) {
  assert(false && "Instruction not implemented");
}

RetInstruction::RetInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::RET, address, data) {}

void RetInstruction::Execute(CpuState & /*state*/) {
  assert(false && "Instruction not implemented");
}

JpInstruction::JpInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::JP, address, data) {
  mExecAddr = data & addr12bit_mask;
}

void JpInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " 0x" << std::hex << mExecAddr;
}

void JpInstruction::Execute(CpuState &state) { state.registers.PC = mExecAddr; }

CallInstruction::CallInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::CALL, address, data) {
  mExecAddr = data & addr12bit_mask;
}

void CallInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " 0x" << std::hex << mExecAddr;
}

void CallInstruction::Execute(CpuState & /*state*/) {
  assert(false && "Instruction not implemented");
}

SexkkInstruction::SexkkInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::SExkk, address, data) {
  mRegister = static_cast<cpu::Register>((data & regx_mask) >> 8);
  mConstant = data & const_mask;
}

void SexkkInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " " << cpu::ToString(mRegister) << " 0x" << std::hex
     << static_cast<unsigned int>(mConstant);
}

void SexkkInstruction::Execute(CpuState &state) {
  const auto &reg = ::GetRegister(mRegister, state);
  if (reg == mConstant) {
    ++state.registers.PC;
  }
}

SexyInstruction::SexyInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::SExy, address, data) {
  mRegisterX = static_cast<cpu::Register>((data & regx_mask) >> 8);
  mRegisterY = static_cast<cpu::Register>((data & regy_mask) >> 4);
}

void SexyInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " " << cpu::ToString(mRegisterX) << " " << cpu::ToString(mRegisterY);
}

void SexyInstruction::Execute(CpuState &state) {
  const auto &regx = ::GetRegister(mRegisterX, state);
  const auto &regy = ::GetRegister(mRegisterY, state);
  if (regx == regy) {
    ++state.registers.PC;
  }
}

SnexkkInstruction::SnexkkInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::SNExkk, address, data) {
  mRegister = static_cast<cpu::Register>((data & regx_mask) >> 8);
  mConstant = data & const_mask;
}

void SnexkkInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " " << cpu::ToString(mRegister) << " 0x" << std::hex
     << static_cast<unsigned int>(mConstant);
}

void SnexkkInstruction::Execute(CpuState &state) {
  const auto &reg = ::GetRegister(mRegister, state);
  if (reg != mConstant) {
    ++state.registers.PC;
  }
}

SnexyInstruction::SnexyInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::SNExy, address, data) {
  mRegisterX = static_cast<cpu::Register>((data & regx_mask) >> 8);
  mRegisterY = static_cast<cpu::Register>((data & regy_mask) >> 4);
}

void SnexyInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " " << cpu::ToString(mRegisterX) << " " << cpu::ToString(mRegisterY);
}

void SnexyInstruction::Execute(CpuState &state) {
  const auto &regx = ::GetRegister(mRegisterX, state);
  const auto &regy = ::GetRegister(mRegisterY, state);
  if (regx != regy) {
    ++state.registers.PC;
  }
}

LdxkkInstruction::LdxkkInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::LDxkk, address, data) {
  mRegister = static_cast<cpu::Register>((data & regx_mask) >> 8);
  mConstant = data & const_mask;
}

void LdxkkInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " " << cpu::ToString(mRegister) << " 0x" << std::hex
     << static_cast<unsigned int>(mConstant);
}

void LdxkkInstruction::Execute(CpuState &state) {
  auto &reg = ::GetRegister(mRegister, state);
  reg = mConstant;
}

LdxyInstruction::LdxyInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::LDxy, address, data) {
  mRegisterX = static_cast<cpu::Register>((data & regx_mask) >> 8);
  mRegisterY = static_cast<cpu::Register>((data & regy_mask) >> 4);
}

void LdxyInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " " << cpu::ToString(mRegisterX) << " " << cpu::ToString(mRegisterY);
}

void LdxyInstruction::Execute(CpuState &state) {
  auto &regx = ::GetRegister(mRegisterX, state);
  const auto &regy = ::GetRegister(mRegisterY, state);
  regx = regy;
}

AddInstruction::AddInstruction(std::uint8_t address, std::uint16_t data)
    : Instruction(Opcode::ADD, address, data) {
  mRegister = static_cast<cpu::Register>((data & regx_mask) >> 8);
  mConstant = data & const_mask;
}

void AddInstruction::Dump(std::ostream &os) {
  Instruction::Dump(os);
  os << " " << cpu::ToString(mRegister) << " 0x" << std::hex
     << static_cast<unsigned int>(mConstant);
}

void AddInstruction::Execute(CpuState &state) {
  auto &reg = ::GetRegister(mRegister, state);
  reg = reg + mConstant;
}

} // namespace Instructions

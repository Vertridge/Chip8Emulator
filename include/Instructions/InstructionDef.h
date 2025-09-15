#pragma once

#include "Instruction.h"
#include "Instructions/InstructionUtil.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

#define U(n) std::uint16_t(n)

namespace Instructions {

inline std::uint16_t GetMaskShifts(std::uint16_t mask) {
  if (mask == 0) {
    return 0;
  }
  if ((mask & 0x000F) != 0) {
    return 0;
  }
  if ((mask & 0x00F0) != 0) {
    return 1;
  }
  if ((mask & 0x0F00) != 0) {
    return 2;
  }
  assert(false && "0xF000 always contains the opcode");
  return 0;
  // std::uint8_t result = 0;
  // std::uint8_t shiftMask = 0x000F;
  // while ((mask & shiftMask) == 0) {
  //   result += 1;
  //   mask = mask >> 1;
  // }
  // return result;
}

class InstructionDef {
public:
  InstructionDef(std::uint16_t opcodeNum, Opcode opcode,
                 std::uint16_t immidiates, std::array<std::uint16_t, 4> masks);
  bool ContainsOpcode(std::uint16_t data) const;
  Opcode GetOpcode() const { return mOpcode; }
  std::string GetNemonic() const { return ToString(mOpcode); }
  std::uint16_t GetOpcodeNum() const { return mOpcodeNum; }
  std::uint16_t GetImmidiates() const { return mImmidiates; }

private:
  std::uint16_t mOpcodeNum;
  Opcode mOpcode;
  std::uint16_t mImmidiates;
  // 4 masks
  // {op, imm1, imm2, imm3}
  std::array<std::uint16_t, 4> mMasks;
};

// clang-format off
const std::array<InstructionDef, 35> InstructionDefinitions{{
    {U(0x00E0), Opcode::CLS, 0, {U(0x00FF), U(0x0000), U(0x0000), U(0x0000)}},
    {U(0x00EE), Opcode::RET, 0, {U(0x00FF), U(0x0000), U(0x0000), U(0x0000)}},
    {U(0x0000), Opcode::SYS, 1, {U(0xF000), U(0x0FFF), U(0x0000), U(0x0000)}},
    {U(0x1000), Opcode::JP, 1, {U(0xF000), U(0x0FFF), U(0x0000), U(0x0000)}},
    {U(0x2000), Opcode::CALL, 1, {U(0xF000), U(0x0FFF), U(0x0000), U(0x0000)}},
    {U(0x3000), Opcode::SExkk, 2, {U(0xF000), U(0x0F00), U(0x00FF), U(0x0000)}},
    {U(0x4000), Opcode::SNExkk, 2, {U(0xF000), U(0x0F00), U(0x00FF), U(0x0000)}},
    {U(0x5000), Opcode::SExy, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x6000), Opcode::LDxkk, 2, {U(0xF000), U(0x0F00), U(0x00FF), U(0x0000)}},
    {U(0x7000), Opcode::ADDxkk, 2, {U(0xF000), U(0x0F00), U(0x00FF), U(0x0000)}},
    {U(0x8000), Opcode::LDxy, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x8001), Opcode::OR, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x8002), Opcode::AND, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x8003), Opcode::XOR, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x8004), Opcode::ADDxy, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x8005), Opcode::SUB, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x8006), Opcode::SHR, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x8007), Opcode::SUBN, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x800E), Opcode::SHL, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0x9000), Opcode::SNExy, 2, {U(0xF00F), U(0x0F00), U(0x00F0), U(0x0000)}},
    {U(0xA000), Opcode::LDnnn, 1, {U(0xF000), U(0x0FFF), U(0x0000), U(0x0000)}},
    {U(0xB000), Opcode::JP, 1, {U(0xF000), U(0x0FFF), U(0x0000), U(0x0000)}},
    {U(0xC000), Opcode::RND, 2, {U(0xF000), U(0x0F00), U(0x00FF), U(0x0000)}},
    {U(0xD000), Opcode::DRW, 3, {U(0xF000), U(0x0F00), U(0x00F0), U(0x000F)}},
    {U(0xE09E), Opcode::SKP, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xE0A1), Opcode::SKNP, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF007), Opcode::LDxdt, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF00A), Opcode::LDx0, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF015), Opcode::LDdtx, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF018), Opcode::LDstx, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF01E), Opcode::ADDix, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF029), Opcode::LDfx, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF033), Opcode::LDbx, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF055), Opcode::LDix, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
    {U(0xF065), Opcode::LDxi, 1, {U(0xF0FF), U(0x0F00), U(0x0000), U(0x0000)}},
}};
// clang-format on

} // namespace Instructions

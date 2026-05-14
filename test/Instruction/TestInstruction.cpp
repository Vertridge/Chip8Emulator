#include "Output/Sprites.h"
#include "catch.hpp"

#include "CPU/CpuUtil.h"
#include "Instructions/Instruction.h"

#include <sstream>

using namespace Instructions;

void Verify(Instruction *instr, std::string expected) {
  std::ostringstream os;
  instr->Dump(os);
  INFO("" << os.str() << "!=" << expected);
  CHECK(os.str() == expected);
}

TEST_CASE("Dump Instruction") {

  SECTION("Base instruction") {
    auto baseInstr = Instruction(Opcode::ADDix, 0x0, 0x0);
    Verify(&baseInstr, "0x0\t0\tADD");
  }

  SECTION("Sys") {
    auto sysInstr = SysInstruction(0x0, 0x0FFF);
    Verify(&sysInstr, "0x0\tfff\tSYS 0xfff");
  }

  SECTION("Cls") {
    auto clsInstr = ClsInstruction(0x0, 0x00E0);
    Verify(&clsInstr, "0x0\te0\tCLS");
  }

  SECTION("Ret") {
    auto retInstr = RetInstruction(0x0, 0x00EE);
    Verify(&retInstr, "0x0\tee\tRET");
  }

  SECTION("Rand") {
    auto randInstr = RndInstruction(0x0, 0xC10F);
    Verify(&randInstr, "0x0\tc10f\tRND V1 0xf");

    CpuState state;
    state.registers.V1 = 0xFF;
    randInstr.Execute(state);

    CHECK(state.registers.V1 <= 0xF);
  }

  SECTION("Call") {
    auto callInstr = CallInstruction(0x0, 0x2FFF);
    Verify(&callInstr, "0x0\t2fff\tCALL 0xfff");
  }

  SECTION("Sexkk") {
    auto sexkkInstr = SexkkInstruction(0x0, 0x310F);
    Verify(&sexkkInstr, "0x0\t310f\tSE V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    sexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 2);

    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    sexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 0);
  }

  SECTION("Sexy") {
    auto sexyInstr = SexyInstruction(0x0, 0x5010);
    Verify(&sexyInstr, "0x0\t5010\tSE V0 V1");

    CpuState state;
    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    sexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 2);

    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    sexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 0);
  }

  SECTION("Snexkk") {
    auto snexkkInstr = SnexkkInstruction(0x0, 0x410F);
    Verify(&snexkkInstr, "0x0\t410f\tSNE V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    snexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 0);

    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    snexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 2);
  }

  SECTION("Snexy") {
    auto snexyInstr = SnexyInstruction(0x0, 0x9010);
    Verify(&snexyInstr, "0x0\t9010\tSNE V0 V1");

    CpuState state;
    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    snexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 0);

    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    snexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 2);
  }

  SECTION("Jp") {
    auto jpInstr = JpInstruction(0x0, 0x1FFF);
    Verify(&jpInstr, "0x0\t1fff\tJP 0xfff");
  }

  SECTION("Ldxkk") {
    auto ldxkkInstr = LdxkkInstruction(0x0, 0x610F);
    Verify(&ldxkkInstr, "0x0\t610f\tLD V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0;
    ldxkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
  }

  SECTION("Ldxy") {
    auto ldxyInstr = LdxyInstruction(0x0, 0x8010);
    Verify(&ldxyInstr, "0x0\t8010\tLD V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0F;
    ldxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
  }

  SECTION("Ldnnn") {
    auto ldnnn = LdnnnInstruction(0x0, 0xA010);
    Verify(&ldnnn, "0x0\ta010\tLD I 0x10");

    CpuState state;
    state.registers.I = 0x0;
    ldnnn.Execute(state);
    CHECK(state.registers.I == 0x10);
  }

  SECTION("Ldxdt") {
    auto ldxdt = LdxdtInstruction(0x0, 0xF107);
    Verify(&ldxdt, "0x0\tf107\tLD V1 VDelay");

    CpuState state;
    state.registers.V1 = 0;
    state.registers.VDelay = 0xFF;
    ldxdt.Execute(state);
    CHECK(state.registers.V1 == state.registers.VDelay);
    CHECK(state.registers.V1 == 0xFF);
  }

  SECTION("Lddtx") {
    auto lddtx = LddtxInstruction(0x0, 0xF115);
    Verify(&lddtx, "0x0\tf115\tLD VDelay V1");

    CpuState state;
    state.registers.V1 = 0xFF;
    state.registers.VDelay = 0;
    lddtx.Execute(state);
    CHECK(state.registers.V1 == state.registers.VDelay);
    CHECK(state.registers.V1 == 0xFF);
  }

  SECTION("Ldstx") {
    auto lddtx = LdstxInstruction(0x0, 0xF107);
    Verify(&lddtx, "0x0\tf107\tLD VSound V1");

    CpuState state;
    state.registers.V1 = 0xFF;
    state.registers.VSound = 0;
    lddtx.Execute(state);
    CHECK(state.registers.V1 == state.registers.VSound);
    CHECK(state.registers.V1 == 0xFF);
  }

  SECTION("Ldfx") {
    auto ldfxInstr = LdfxInstruction(0x0, 0xF129);
    Verify(&ldfxInstr, "0x0\tf129\tLD F V1");

    CpuState state;
    state.registers.V1 = 0x1;
    ldfxInstr.Execute(state);
    CHECK(state.registers.I == Output::Sprites::sprite_1_address);
  }

  SECTION("Ldix") {
    auto ldix = LdixInstruction(0x0, 0xFF55);
    Verify(&ldix, "0x0\tff55\tLD [I] VF");

    CpuState state;
    state.registers.I = cpu::memory_start;
    for (int i = 0; i < static_cast<int>(Register::VF); ++i) {
      auto &reg = cpu::GetRegister(static_cast<Register>(i), state);
      reg = static_cast<std::uint8_t>(i);
      CHECK(state.memory.Read(state.registers.I + i) == 0);
    }
    ldix.Execute(state);
    for (int i = 0; i < static_cast<int>(Register::VF); ++i) {
      const auto &reg = cpu::GetRegister(static_cast<Register>(i), state);
      CHECK(state.memory.Read(state.registers.I + i) ==
            static_cast<std::uint8_t>(i));
      CHECK(state.memory.Read(state.registers.I + i) == reg);
    }
  }

  SECTION("Ldxi") {
    auto ldxi = LdxiInstruction(0x0, 0xFF65);
    Verify(&ldxi, "0x0\tff65\tLD VF [I]");

    CpuState state;
    state.registers.I = cpu::memory_start;
    for (int i = 0; i < static_cast<int>(Register::VF); ++i) {
      auto &reg = cpu::GetRegister(static_cast<Register>(i), state);
      reg = 0;
      state.memory.Write(state.registers.I + i, static_cast<std::uint8_t>(i));
    }
    ldxi.Execute(state);
    for (int i = 0; i < static_cast<int>(Register::VF); ++i) {
      const auto &reg = cpu::GetRegister(static_cast<Register>(i), state);
      CHECK(reg == static_cast<std::uint8_t>(i));
      CHECK(reg == state.memory.Read(state.registers.I + i));
    }
  }

  SECTION("Addxkk") {
    auto addxkkInstr = AddxkkInstruction(0x0, 0x710F);
    Verify(&addxkkInstr, "0x0\t710f\tADD V1 0xf");

    CpuState state;
    addxkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V1 = 0x10;
    addxkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x1F);
  }

  SECTION("Addxy") {
    auto addxyInstr = AddxyInstruction(0x0, 0x8014);
    Verify(&addxyInstr, "0x0\t8014\tADD V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0F;
    addxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0;
    addxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.V1 == 0x0);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0b010101;
    state.registers.V1 = 0b101010;
    addxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0b111111);
    CHECK(state.registers.V1 == 0b101010);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0xFF;
    state.registers.V1 = 0x01;
    addxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.VF == 0x1);

    state.registers.V0 = 0xFF;
    state.registers.V1 = 0xFF;
    addxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0xFE);
    CHECK(state.registers.V1 == 0xFF);
    CHECK(state.registers.VF == 0x1);
  }

  SECTION("Addix") {
    auto addixInstr = AddixInstruction(0x0, 0xF31E);
    Verify(&addixInstr, "0x0\tf31e\tADD I V3");

    CpuState state;
    state.registers.I = 0;
    state.registers.V3 = 0;
    addixInstr.Execute(state);
    CHECK(state.registers.I == 0x0);

    state.registers.I = 0;
    state.registers.V3 = 0x10;
    addixInstr.Execute(state);
    CHECK(state.registers.I == 0x10);

    state.registers.I = 0x10;
    state.registers.V3 = 0x10;
    addixInstr.Execute(state);
    CHECK(state.registers.I == 0x20);
  }

  SECTION("Sub") {
    auto subInstr = SubInstruction(0x0, 0x8015);
    Verify(&subInstr, "0x0\t8015\tSUB V0 V1");

    CpuState state;
    state.registers.V0 = 0xFF;
    state.registers.V1 = 0x0F;
    subInstr.Execute(state);
    CHECK(state.registers.V0 == 0xF0);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.VF == 0x1);

    state.registers.V0 = 0xFF;
    state.registers.V1 = 0xFF;
    subInstr.Execute(state);
    CHECK(state.registers.V0 == 0x00);
    CHECK(state.registers.V1 == 0xFF);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0x0F;
    state.registers.V1 = 0xFF;
    subInstr.Execute(state);
    CHECK(state.registers.V0 == 0x10);
    CHECK(state.registers.V1 == 0xFF);
    CHECK(state.registers.VF == 0x0);
  }

  SECTION("Subn") {
    auto subnInstr = SubnInstruction(0x0, 0x8017);
    Verify(&subnInstr, "0x0\t8017\tSUBN V0 V1");

    CpuState state;
    state.registers.V0 = 0xFF;
    state.registers.V1 = 0x0F;
    subnInstr.Execute(state);
    CHECK(state.registers.V0 == 0xF0);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0xFF;
    state.registers.V1 = 0xFF;
    subnInstr.Execute(state);
    CHECK(state.registers.V0 == 0x00);
    CHECK(state.registers.V1 == 0xFF);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0x0F;
    state.registers.V1 = 0xFF;
    subnInstr.Execute(state);
    CHECK(state.registers.V0 == 0x10);
    CHECK(state.registers.V1 == 0xFF);
    CHECK(state.registers.VF == 0x1);
  }

  SECTION("Or") {
    auto orInstr = OrInstruction(0x0, 0x8011);
    Verify(&orInstr, "0x0\t8011\tOR V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0F;
    orInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0;
    orInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.V1 == 0x0);

    state.registers.V0 = 0b010101;
    state.registers.V1 = 0b101010;
    orInstr.Execute(state);
    CHECK(state.registers.V0 == 0b111111);
    CHECK(state.registers.V1 == 0b101010);
  }

  SECTION("And") {
    auto orInstr = AndInstruction(0x0, 0x8012);
    Verify(&orInstr, "0x0\t8012\tAND V0 V1");

    CpuState state;
    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x0F;
    orInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0F;
    orInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V0 = 0b010101;
    state.registers.V1 = 0b101010;
    orInstr.Execute(state);
    CHECK(state.registers.V0 == 0b0);
    CHECK(state.registers.V1 == 0b101010);

    state.registers.V0 = 0b001111;
    state.registers.V1 = 0b101010;
    orInstr.Execute(state);
    CHECK(state.registers.V0 == 0b1010);
    CHECK(state.registers.V1 == 0b101010);
  }

  SECTION("Xor") {
    auto xorInstr = XorInstruction(0x0, 0x8013);
    Verify(&xorInstr, "0x0\t8013\tXOR V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0F;
    xorInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0;
    xorInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.V1 == 0x0);

    state.registers.V0 = 0b010101;
    state.registers.V1 = 0b101010;
    xorInstr.Execute(state);
    CHECK(state.registers.V0 == 0b111111);
    CHECK(state.registers.V1 == 0b101010);

    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x0F;
    xorInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V0 = 0b00001111;
    state.registers.V1 = 0b10101010;
    xorInstr.Execute(state);
    CHECK(state.registers.V0 == 0b10100101);
    CHECK(state.registers.V1 == 0b10101010);
  }

  SECTION("Shr") {
    auto shrInstr = ShrInstruction(0x0, 0x8016);
    Verify(&shrInstr, "0x0\t8016\tSHR V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    shrInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0x1;
    shrInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.VF == 0x1);

    state.registers.V0 = 0x2;
    shrInstr.Execute(state);
    CHECK(state.registers.V0 == 0x1);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0xFF;
    shrInstr.Execute(state);
    CHECK(state.registers.V0 == 0x7F);
    CHECK(state.registers.VF == 0x1);

    state.registers.V0 = 0b10101010;
    shrInstr.Execute(state);
    CHECK(state.registers.V0 == 0b01010101);
    CHECK(state.registers.VF == 0b0);
  }

  SECTION("Shl") {
    auto shlInstr = ShlInstruction(0x0, 0x801E);
    Verify(&shlInstr, "0x0\t801e\tSHL V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    shlInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0x1;
    shlInstr.Execute(state);
    CHECK(state.registers.V0 == 0x2);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0x2;
    shlInstr.Execute(state);
    CHECK(state.registers.V0 == 0x4);
    CHECK(state.registers.VF == 0x0);

    state.registers.V0 = 0xF0;
    shlInstr.Execute(state);
    CHECK(state.registers.V0 == 0xE0);
    CHECK(state.registers.VF == 0x1);

    state.registers.V0 = 0b10101010;
    shlInstr.Execute(state);
    CHECK(state.registers.V0 == 0b01010100);
    CHECK(state.registers.VF == 0b1);
  }

  SECTION("Drw") {
    auto drwInstr = DrwInstruction(0x0, 0xD012);
    Verify(&drwInstr, "0x0\td012\tDRAW V0 V1 0x2");
  }
}

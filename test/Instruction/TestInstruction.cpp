#include "catch.hpp"

#include "Instructions/Instruction.h"

#include <iostream>
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
    Verify(&baseInstr, "0x0 ADD");
  }

  SECTION("Sys") {
    auto sysInstr = SysInstruction(0x0, 0x0FFF);
    Verify(&sysInstr, "0x0 SYS 0xfff");
  }

  SECTION("Cls") {
    auto clsInstr = ClsInstruction(0x0, 0x00E0);
    Verify(&clsInstr, "0x0 CLS");
  }

  SECTION("Ret") {
    auto retInstr = RetInstruction(0x0, 0x00EE);
    Verify(&retInstr, "0x0 RET");
  }

  SECTION("Call") {
    auto callInstr = CallInstruction(0x0, 0x2FFF);
    Verify(&callInstr, "0x0 CALL 0xfff");
  }

  SECTION("Sexkk") {
    auto sexkkInstr = SexkkInstruction(0x0, 0x310F);
    Verify(&sexkkInstr, "0x0 SE V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    sexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 1);

    state.registers.V1 = 0x01;
    state.registers.PC = 0;
    sexkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x01);
    CHECK(state.registers.PC == 0);
  }

  SECTION("Sexy") {
    auto sexyInstr = SexyInstruction(0x0, 0x5010);
    Verify(&sexyInstr, "0x0 SE V0 V1");

    CpuState state;
    state.registers.V0 = 0x0F;
    state.registers.V1 = 0x0F;
    state.registers.PC = 0;
    sexyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
    CHECK(state.registers.PC == 1);

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
    Verify(&snexkkInstr, "0x0 SNE V1 0xf");

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
    CHECK(state.registers.PC == 1);
  }

  SECTION("Snexy") {
    auto snexyInstr = SnexyInstruction(0x0, 0x9010);
    Verify(&snexyInstr, "0x0 SNE V0 V1");

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
    CHECK(state.registers.PC == 1);
  }

  SECTION("Jp") {
    auto jpInstr = JpInstruction(0x0, 0x1FFF);
    Verify(&jpInstr, "0x0 JP 0xfff");
  }

  SECTION("Ldxkk") {
    auto ldxkkInstr = LdxkkInstruction(0x0, 0x610F);
    Verify(&ldxkkInstr, "0x0 LD V1 0xf");

    CpuState state;
    state.registers.V1 = 0x0;
    ldxkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);
  }

  SECTION("Ldxy") {
    auto ldxyInstr = LdxyInstruction(0x0, 0x8010);
    Verify(&ldxyInstr, "0x0 LD V0 V1");

    CpuState state;
    state.registers.V0 = 0x0;
    state.registers.V1 = 0x0F;
    ldxyInstr.Execute(state);
    CHECK(state.registers.V0 == 0x0F);
    CHECK(state.registers.V1 == 0x0F);
  }

  SECTION("Ldnnn") {
    auto ldnnn = LdnnnInstruction(0x0, 0xA010);
    Verify(&ldnnn, "0x0 LD I 0x10");

    CpuState state;
    state.registers.I = 0x0;
    ldnnn.Execute(state);
    CHECK(state.registers.I == 0x10);
  }

  SECTION("Ldxdt") {
    auto ldxdt = LdxdtInstruction(0x0, 0xF107);
    Verify(&ldxdt, "0x0 LD V1 VDelay");

    CpuState state;
    state.registers.V1 = 0;
    state.registers.VDelay = 0xFF;
    ldxdt.Execute(state);
    CHECK(state.registers.V1 == state.registers.VDelay);
    CHECK(state.registers.V1 == 0xFF);
  }

  SECTION("Lddtx") {
    auto lddtx = LddtxInstruction(0x0, 0xF107);
    Verify(&lddtx, "0x0 LD VDelay V1");

    CpuState state;
    state.registers.V1 = 0xFF;
    state.registers.VDelay = 0;
    lddtx.Execute(state);
    CHECK(state.registers.V1 == state.registers.VDelay);
    CHECK(state.registers.V1 == 0xFF);
  }

  SECTION("Ldstx") {
    auto lddtx = LdstxInstruction(0x0, 0xF107);
    Verify(&lddtx, "0x0 LD VSound V1");

    CpuState state;
    state.registers.V1 = 0xFF;
    state.registers.VSound = 0;
    lddtx.Execute(state);
    CHECK(state.registers.V1 == state.registers.VSound);
    CHECK(state.registers.V1 == 0xFF);
  }

  SECTION("Addxkk") {
    auto addxkkInstr = AddxkkInstruction(0x0, 0x710F);
    Verify(&addxkkInstr, "0x0 ADD V1 0xf");

    CpuState state;
    addxkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x0F);

    state.registers.V1 = 0x10;
    addxkkInstr.Execute(state);
    CHECK(state.registers.V1 == 0x1F);
  }

  SECTION("Addxy") {
    auto addxyInstr = AddxyInstruction(0x0, 0x8014);
    Verify(&addxyInstr, "0x0 ADD V0 V1");

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

  SECTION("Sub") {
    auto subInstr = SubInstruction(0x0, 0x8015);
    Verify(&subInstr, "0x0 SUB V0 V1");

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
    Verify(&subnInstr, "0x0 SUBN V0 V1");

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
    Verify(&orInstr, "0x0 OR V0 V1");

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
    Verify(&orInstr, "0x0 AND V0 V1");

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
    Verify(&xorInstr, "0x0 XOR V0 V1");

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
    Verify(&shrInstr, "0x0 SHR V0 V1");

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
    Verify(&shlInstr, "0x0 SHL V0 V1");

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
}

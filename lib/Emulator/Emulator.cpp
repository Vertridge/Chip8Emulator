#include "Emulator/Emulator.h"
#include <Instructions/Disassembler.h>
#include <Output/Sprites.h>

#include <algorithm>
#include <assert.h>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <system_error>

namespace emulator {

namespace {
std::vector<std::uint8_t> ReadFileToVector(const std::filesystem::path &file) {
  std::ifstream ifs(file.string(), std::ios::binary | std::ios::ate);
  if (!ifs) {
    std::cerr << "Failed to open file: " << file << std::endl;
    return {};
  }
  const std::streamsize size = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::vector<std::uint8_t> inputBuff(size);

  if (!ifs.read(reinterpret_cast<char *>(inputBuff.data()), size)) {
    std::cerr << "Failed to read file: " << file << std::endl;
    return {};
  }

  return inputBuff;
}
} // namespace

Emulator::Emulator() : mRunning(false) {}

Emulator::~Emulator() {
  std::for_each(mInstructions.begin(), mInstructions.end(),
                [](auto *instruction) { free(instruction); });
}

bool Emulator::LoadGame(const std::filesystem::path path) {
  std::error_code error;
  auto result = std::filesystem::exists(path, error);
  if (error) {
    std::cerr << "Failed to load: " << path << error.message();
    return false;
  }
  if (!result) {
    std::cerr << "Failed to load: '" << path << "', file does not exist\n";
    return false;
  }
  // Load game into memory
  mState.registers.PC = instruction_start;
  auto inputBuffer = ReadFileToVector(path);

  std::cout << "inputBuffer size: " << inputBuffer.size() << std::endl;
  for (const auto &byte : inputBuffer) {
    std::cout << std::hex << (std::uint32_t)byte << " ";
  }
  std::cout << std::endl;
  mState.memory.LoadIntoMemory(std::move(inputBuffer), instruction_start);
  if (!LoadSprites()) {
    std::cerr << "Failed to load sprites" << std::endl;
    return false;
  }

  mState.memory.Dump(std::cout);
  return true;
}

void Emulator::Run(bool dumpState) {
  mRunning = true;
  if (dumpState) {
    DumpState(std::cout);
  }
  while (mRunning) {
    auto *instruction = GetNextInstruction();
    instruction->Dump(std::cout);
    std::cout << "\n";

    ExecuteInstruction(instruction);

    if (dumpState) {
      DumpState(std::cout);
    }

    delete instruction;
  }
}

Instructions::Instruction *Emulator::GetNextInstruction() {
  auto instructionBytes = mState.memory.ReadUint16(mState.registers.PC);
  return Disassembler::Disassemble(instructionBytes, mState.registers.PC);
}

void Emulator::ExecuteInstruction(Instructions::Instruction *instruction) {
  instruction->Execute(mState);
  mState.registers.PC += Instructions::instruction_size;
}

void Emulator::DumpState(std::ostream &os) {
  os << "Dump registers: \n"
     << "\tV0: 0x" << std::hex << (std::uint16_t)mState.registers.V0
     << "\tV1: 0x" << std::hex << (std::uint16_t)mState.registers.V1
     << "\tV2: 0x" << std::hex << (std::uint16_t)mState.registers.V2
     << "\tV3: 0x" << std::hex << (std::uint16_t)mState.registers.V3 << "\n"
     << "\tV4: 0x" << std::hex << (std::uint16_t)mState.registers.V4
     << "\tV5: 0x" << std::hex << (std::uint16_t)mState.registers.V5
     << "\tV6: 0x" << std::hex << (std::uint16_t)mState.registers.V6
     << "\tV7: 0x" << std::hex << (std::uint16_t)mState.registers.V7 << "\n"
     << "\tV8: 0x" << std::hex << (std::uint16_t)mState.registers.V8
     << "\tV9: 0x" << std::hex << (std::uint16_t)mState.registers.V9
     << "\tVA: 0x" << std::hex << (std::uint16_t)mState.registers.VA << "\n"
     << "\tVB: 0x" << std::hex << (std::uint16_t)mState.registers.VB
     << "\tVC: 0x" << std::hex << (std::uint16_t)mState.registers.VC
     << "\tVD: 0x" << std::hex << (std::uint16_t)mState.registers.VD << "\n"
     << "\tVE: 0x" << std::hex << (std::uint16_t)mState.registers.VE
     << "\tVF: 0x" << std::hex << (std::uint16_t)mState.registers.VF << "\n";
}

bool Emulator::LoadSprites() {
  std::cout << "Loading Sprites" << std::endl;
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_0_address,
                                Output::Sprites::sprite_0)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_1_address,
                                Output::Sprites::sprite_1)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_2_address,
                                Output::Sprites::sprite_2)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_3_address,
                                Output::Sprites::sprite_3)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_4_address,
                                Output::Sprites::sprite_4)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_5_address,
                                Output::Sprites::sprite_5)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_6_address,
                                Output::Sprites::sprite_6)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_7_address,
                                Output::Sprites::sprite_7)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_8_address,
                                Output::Sprites::sprite_8)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_9_address,
                                Output::Sprites::sprite_9)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_A_address,
                                Output::Sprites::sprite_A)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_B_address,
                                Output::Sprites::sprite_B)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_C_address,
                                Output::Sprites::sprite_C)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_D_address,
                                Output::Sprites::sprite_D)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_E_address,
                                Output::Sprites::sprite_E)) {
    return false;
  }
  if (!mState.memory.LoadSprite(Output::Sprites::sprite_F_address,
                                Output::Sprites::sprite_F)) {
    return false;
  }

  return true;
}

} // namespace emulator

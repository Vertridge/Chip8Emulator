#include "Emulator/Emulator.h"
#include <Instructions/Disassembler.h>

#include <algorithm>
#include <assert.h>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <iterator>
#include <system_error>

namespace emulator {

namespace {
std::vector<std::uint8_t> ReadFileToVector(const std::filesystem::path &file) {
  std::ifstream is(file.string(), std::ios::binary);
  if (!is) {
    std::cerr << "Failed to open file: " << file << std::endl;
    return {};
  }
  std::istream_iterator<std::uint8_t> start(is), end;
  std::vector<std::uint8_t> inputBuff(start, end);

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
  mState.memory.Dump(std::cout);
  return true;
}

void Emulator::Run() {
  mRunning = true;

  while (mRunning) {
    auto *instruction = GetNextInstruction();
    instruction->Dump(std::cout);
    std::cout << "\n";

    ExecuteInstruction(instruction);
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

} // namespace emulator

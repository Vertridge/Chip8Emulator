#include "Emulator.h"

#include <algorithm>
#include <assert.h>
#include <iostream>

namespace emulator {

Emulator::Emulator(std::vector<Instructions::Instruction *> instructions)
    : mInstructions(std::move(instructions)), mRunning(false) {
  mState.registers.PC = instruction_start;
}

Emulator::~Emulator() {
  std::for_each(mInstructions.begin(), mInstructions.end(),
                [](auto *instruction) { free(instruction); });
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
  auto address = mState.registers.PC;
  auto instruction = std::find_if(
      mInstructions.begin(), mInstructions.end(),
      [&](auto *instruction) { return instruction->GetAddress() == address; });

  if (instruction == mInstructions.end()) {
    return nullptr;
  }

  return *instruction;
}

void Emulator::ExecuteInstruction(Instructions::Instruction *instruction) {
  instruction->Execute(mState);
  mState.registers.PC += Instructions::instruction_size;
}

} // namespace emulator

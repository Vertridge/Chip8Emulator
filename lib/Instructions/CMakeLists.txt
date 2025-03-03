add_library(Instructions InstructionDef.cpp Disassembler.cpp InstructionUtil.cpp Instruction.cpp)
target_link_libraries(Instructions Cpu)

add_executable(Emulator Emulator.cpp main.cpp)
target_link_libraries(Emulator Instructions Cpu Input)

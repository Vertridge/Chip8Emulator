set(TEST_FILES 
	main.cpp 
	TestInstruction.cpp)

add_executable(test_instruction ${TEST_FILES})

target_link_libraries(test_instruction
					  Catch Instructions)

add_test(NAME test_instruction COMMAND test_instruction)

add_dependencies(unittests test_instruction)

set(TEST_FILES 
	main.cpp 
	TestCPU.cpp)

add_executable(test_cpu ${TEST_FILES})

target_link_libraries(test_cpu
					  Catch Cpu)

add_test(NAME test_cpu COMMAND test_cpu)

add_dependencies(unittests test_cpu)

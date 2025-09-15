set(TEST_FILES 
	main.cpp 
	TestKeys.cpp)

add_executable(test_input ${TEST_FILES})

target_link_libraries(test_input
					  Catch Input)

add_test(NAME test_input COMMAND test_input)

add_dependencies(unittests test_input)

set(TEST_FILES 
	main.cpp 
	TestDisplay.cpp)

add_executable(test_output ${TEST_FILES})

target_link_libraries(test_output
					  Catch Output)

add_test(NAME test_output COMMAND test_output)

add_dependencies(unittests test_output)

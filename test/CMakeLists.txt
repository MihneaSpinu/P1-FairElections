# Add the test executable
add_executable(test_runner test.c)

# Link the shared library to the test executable
target_link_libraries(test_runner PRIVATE shared)

# Include the shared header file directory
target_include_directories(test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)

# Add a test case
add_test(NAME MyTest COMMAND test_runner)

cmake_minimum_required(VERSION 3.10)

# Project name
project(P1_Projekt)

# Specify the C standard
set(CMAKE_C_STANDARD 11)

# Collect all source files in the directory except main.c
file(GLOB SHARED_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
list(REMOVE_ITEM SHARED_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.c")

# Add a library for all shared files
add_library(shared ${SHARED_SOURCES})

# Add the main executable
add_executable(P1_Projekt main.c)

# Link the shared library to the main executable
target_link_libraries(P1_Projekt PRIVATE shared)

# Include the shared header file directory for all targets
target_include_directories(P1_Projekt PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Enable CTest
enable_testing()

# Include the tests directory
add_subdirectory(test)

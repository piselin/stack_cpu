cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME StackCPU)
project(${PROJECT_NAME})


# Options. Turn on with 'cmake -Dmyvarname=ON'.
#option(test "Build all tests." OFF) # Makes boolean 'test' available.

# Compiler
add_definitions(-Wall -std=c++14)

# Normal Executables
add_library(disassembly_lib disassembly.cpp)
add_executable(virtual_cpu stack_processor.cpp)
target_link_libraries(virtual_cpu disassembly_lib)





############# Google Test ##################
set(PROJECT_TEST_NAME ${PROJECT_NAME}_test)
find_package(GTest REQUIRED)

# Include gtest library
include_directories(${GTEST_INCLUDE_DIRS})
set(LINK_LIBS ${LINK_LIBS} ${GTEST_BOTH_LIBRARIES})
message("GTEST_INCLUDE_DIRS" ${GTEST_INCLUDE_DIRS})

# somehow this ins necessary...
find_package(Threads)
set(LINK_LIBS ${LINK_LIBS} ${CMAKE_THREAD_LIBS_INIT})


# Unit tests
add_executable(${PROJECT_TEST_NAME} unit_tests.cpp)
#add_dependencies(${PROJECT_TEST_NAME} gtest)

# linking to gtest
target_link_libraries(${PROJECT_TEST_NAME} ${LINK_LIBS})
target_link_libraries(${PROJECT_TEST_NAME} disassembly_lib)


# make the test runnable with 
# $ make test
enable_testing()
add_test(
	NAME ${PROJECT_TEST_NAME}
	COMMAND ${PROJECT_TEST_NAME}
)

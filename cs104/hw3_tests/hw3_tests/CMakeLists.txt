cmake_minimum_required(VERSION 3.1)

message("########################################################")
message("                 CS104 HW2 Test Suite")
message("########################################################")

project(CS104-HW3-Test-Suite C CXX)

# pick up include files
# ----------------------------------------------------------
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/test_cmake_lib)

include(Policies NO_POLICY_SCOPE)
include(Utils)
include(Shorthand)
include(LibraryUtils)
include(104CompileFlags)

# setup Valgrind
# ----------------------------------------------------------

find_program(VALGRIND NAMES valgrind DOC "Path to valgrind executable")
import_executable(valgrind ${VALGRIND})

set(VALGRIND_ARGS --tool=memcheck 
	--leak-check=yes
	--trace-children=no) # don't valgrind child processes, we control manually which processes are valground

# find GTest
# ----------------------------------------------------------

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

import_libraries(gtest LIBRARIES ${GTEST_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})
import_libraries(gtest_main LIBRARIES ${GTEST_MAIN_LIBRARIES} Threads::Threads INCLUDES ${GTEST_INCLUDE_DIRS})

include(CustomTests)
enable_testing()

# find user code dir
# ----------------------------------------------------------

if(NOT DEFINED HW3_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_BINARY_DIR}/../*.cpp")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw1 dir, or run CMake with the \"-DHW3_DIR=<path to hw3>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_BINARY_DIR}/.." REALPATH)
		message(STATUS "HW3_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW3_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw1 assignment directory")
	endif()
endif()

# make sure HW3_DIR is an absolute path
get_filename_component(HW3_DIR ${HW3_DIR} REALPATH)

# build loose user code as a CMake library
# ----------------------------------------------------------

# now build user code into a CMake library
set(HW3_STACK_SOURCES ${HW3_DIR}/stackint.cpp ${HW3_DIR}/circular_list_int.cpp)

# lots of people may have put stackint.cpp in the wrong place, so give a warning about it and continue if it's missing
if(NOT EXISTS ${HW3_DIR}/stackint.cpp)
	message(WARNING "Missing source file ${HW3_DIR}/stackint.cpp")
	list(REMOVE_ITEM HW3_STACK_SOURCES ${HW3_DIR}/stackint.cpp)
endif()

add_library(hw3_stack STATIC ${HW3_STACK_SOURCES})
target_include_directories(hw3_stack PUBLIC ${HW3_DIR})


# build user parser executable using make
# ----------------------------------------------------------

set(USER_CODE_EXECUTABLE ${HW3_DIR}/parser)

# find all c++ files as dependencies, so that the code can be remade
file(GLOB_RECURSE USER_CODE_DIR_FILES "${HW3_DIR}/*.cpp" "${HW3_DIR}/*.h")

add_custom_command(OUTPUT ${USER_CODE_EXECUTABLE}
		COMMAND make
		WORKING_DIRECTORY ${HW3_DIR}
		VERBATIM
		DEPENDS ${USER_CODE_DIR_FILES}
		COMMENT "Running make in hw3 directory...")

add_custom_target(user_makefile
		ALL
		DEPENDS ${USER_CODE_EXECUTABLE})



# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------

add_subdirectory(stack_tests)
add_subdirectory(arith_parser_tests)

set(TEST_TIMEOUT 60) # seconds

# Test target for to generate grade report
add_custom_target(grade
	COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
	COMMAND make clean
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
	COMMAND make testing_utils
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling stack, output saved to ${COMPILE_LOG_DIR}/stack.complog"
	COMMAND make hw3_stack 1>${COMPILE_LOG_DIR}/stack.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling arith_parser via Makefile, output saved to ${COMPILE_LOG_DIR}/arith_parser.complog"
	COMMAND make user_makefile 1>${COMPILE_LOG_DIR}/arith_parser.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling unit tests"
	COMMAND make all || true
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing                                     # remove any old XML logfiles
	COMMAND ${CMAKE_CTEST_COMMAND} -T Test --no-compress-output -C $<CONFIG> --timeout ${TEST_TIMEOUT} || true   # generate XML logfile
	COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
	COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
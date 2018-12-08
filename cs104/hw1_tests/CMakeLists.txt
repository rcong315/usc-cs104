cmake_minimum_required(VERSION 3.1)

message("########################################################")
message("                 CS104 HW2 Test Suite")
message("########################################################")

project(CS104-HW2-Test-Suite C CXX)

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

set(VALGRIND_ARGS 
	--tool=memcheck 
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

if(NOT DEFINED HW1_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_SOURCE_DIR}/../*.cpp")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw1 dir, or run CMake with the \"-DHW1_DIR=<path to hw1>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_SOURCE_DIR}/.." REALPATH)
		message(STATUS "HW1_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW1_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw1 assignment directory")
	endif()
endif()

# build loose user code as a CMake library
# ----------------------------------------------------------

set(HW1_SOURCES 
	${HW1_DIR}/simpleCharManager.cpp
	${HW1_DIR}/flexCharManager.cpp
	${HW1_DIR}/hw1q5.cpp)


# now build user code into a CMake library
add_library(hw1_simple_char_manager STATIC ${HW1_DIR}/simpleCharManager.cpp)
target_include_directories(hw1_simple_char_manager PUBLIC ${HW1_DIR})

add_library(hw1_flex_char_manager STATIC ${HW1_DIR}/flexCharManager.cpp)
target_include_directories(hw1_flex_char_manager PUBLIC ${HW1_DIR})


# build user executables 
# ----------------------------------------------------------

add_executable(q4_palindrome ${HW1_DIR}/palindrome.cpp)

add_executable(q5_streams ${HW1_DIR}/hw1q5.cpp)

add_executable(first_memtest ${HW1_DIR}/first_memtest.cpp)
target_link_libraries(first_memtest hw1_simple_char_manager)

add_executable(second_memtest ${HW1_DIR}/second_memtest.cpp)
target_link_libraries(second_memtest hw1_flex_char_manager hw1_simple_char_manager)


# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------

add_subdirectory(palindrome)
add_subdirectory(streams)
add_subdirectory(simple_char_manager)
add_subdirectory(flex_char_manager)

set(TEST_TIMEOUT 80) # seconds

# Test target for to generate grade report
add_custom_target(grade
	COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
	COMMAND make clean
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
	COMMAND make testing_utils
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling palindrome, output saved to ${COMPILE_LOG_DIR}/palindrome.complog"
	COMMAND make palindrome_test 1>${COMPILE_LOG_DIR}/palindrome.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling streams, output saved to ${COMPILE_LOG_DIR}/streams.complog"
	COMMAND make streams_test 1>${COMPILE_LOG_DIR}/streams.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling simple char manager, output saved to ${COMPILE_LOG_DIR}/selection_sort.complog"
	COMMAND make simple_char_manager_test 1>${COMPILE_LOG_DIR}/simple_char_manager.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling flex char manager, output saved to ${COMPILE_LOG_DIR}/circular_list.complog"
	COMMAND make flex_char_manager_test 1>${COMPILE_LOG_DIR}/flex_char_manager.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing       # remove any old XML logfiles
	COMMAND ${CMAKE_CTEST_COMMAND} -T Test --no-compress-output -C $<CONFIG> --timeout ${TEST_TIMEOUT} || true             # generate XML logfile
	COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
	COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
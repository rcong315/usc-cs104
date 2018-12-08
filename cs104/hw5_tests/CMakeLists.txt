cmake_minimum_required(VERSION 3.1)

message("########################################################")
message("                 CS104 HW5 Test Suite")
message("########################################################")

project(CS104-HW5-Test-Suite C CXX)

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

if(NOT DEFINED HW5_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_BINARY_DIR}/../*.cpp")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw5 dir, or run CMake with the \"-DHW5_DIR=<path to hw5>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_BINARY_DIR}/.." REALPATH)
		message(STATUS "HW5_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW5_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw5 assignment directory")
	endif()
endif()

# make sure HW5_DIR is an absolute path
get_filename_component(HW5_DIR "${HW5_DIR}" REALPATH)

# build loose user code as a CMake library
# ----------------------------------------------------------

add_library(hw5_functor STATIC ${HW5_DIR}/functor.cpp)
target_include_directories(hw5_functor PUBLIC ${HW5_DIR})

add_library(hw5_msort INTERFACE)
target_include_directories(hw5_functor PUBLIC ${HW5_DIR})
target_link_libraries(hw5_msort INTERFACE hw5_functor)

add_library(hw5_fatalist STATIC ${HW5_DIR}/fatalist.cpp)

# build user executable using make
# ----------------------------------------------------------

set(CAVE_EXECUTABLE ${HW5_DIR}/cave)

add_custom_command(OUTPUT ${CAVE_EXECUTABLE}
		COMMAND make cave
		WORKING_DIRECTORY ${HW5_DIR}
		VERBATIM
		DEPENDS ${HW5_DIR}/cave.cpp
		COMMENT "Running \"make cave\" in hw5 directory...")
add_custom_target(cave_executable
		ALL
		DEPENDS ${CAVE_EXECUTABLE})



# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------

add_subdirectory(cave_tests)
add_subdirectory(functor_tests)
add_subdirectory(msort_tests)
add_subdirectory(fatalist_tests)

set(TEST_TIMEOUT 60) # seconds

# Test target for to generate grade report
add_custom_target(grade
	COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
	COMMAND make clean
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
	COMMAND make testing_utils
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling functor, output saved to ${COMPILE_LOG_DIR}/functor.complog"
	COMMAND make hw5_functor 1>${COMPILE_LOG_DIR}/functor.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling msort, output saved to ${COMPILE_LOG_DIR}/msort.complog"
	COMMAND make msort_test 1>${COMPILE_LOG_DIR}/msort.complog 2>&1 || true                            # compile test suite instead of actual tests because msort is header-only
	COMMAND make msort_runtime_test 1>>${COMPILE_LOG_DIR}/msort.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling fatalist, output saved to ${COMPILE_LOG_DIR}/fatalist.complog"
	COMMAND make hw5_fatalist 1>${COMPILE_LOG_DIR}/fatalist.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling cave via Makefile, output saved to ${COMPILE_LOG_DIR}/cave.complog"
	COMMAND make cave_executable 1>${COMPILE_LOG_DIR}/cave.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling unit tests"
	COMMAND make cave_test || true
	COMMAND make functor_test || true
	COMMAND make fatalist_test || true
	COMMAND make fatalist_runtime_test || true
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing                                     # remove any old XML logfiles
	COMMAND ${CMAKE_CTEST_COMMAND} -T Test --no-compress-output -C $<CONFIG> --timeout ${TEST_TIMEOUT} || true   # generate XML logfile
	COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
	COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
cmake_minimum_required(VERSION 3.1)

message("########################################################")
message("                 CS104 HW6 Test Suite")
message("########################################################")

project(CS104-HW6-Test-Suite C CXX)

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

if(NOT DEFINED HW6_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_BINARY_DIR}/../*.h")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw6 dir, or run CMake with the \"-DHW6_DIR=<path to hw6>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_BINARY_DIR}/.." REALPATH)
		message(STATUS "HW6_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW6_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw6 assignment directory")
	endif()
endif()

# make sure HW6_DIR is an absolute path
get_filename_component(HW6_DIR "${HW6_DIR}" REALPATH)

# build user executables using make
# ----------------------------------------------------------

# use all source files as dependencies so we know when to rerun make
file(GLOB ALL_SOURCE_FILES "${HW6_DIR}/*.h" "${HW6_DIR}/*.cpp")

set(SEARCH_EXECUTABLE ${HW6_DIR}/search)
set(COLORING_EXECUTABLE ${HW6_DIR}/coloring)

add_custom_command(OUTPUT ${SEARCH_EXECUTABLE}
		COMMAND make search
		WORKING_DIRECTORY ${HW6_DIR}
		VERBATIM
		DEPENDS ${ALL_SOURCE_FILES}
		COMMENT "Running \"make search\" in hw6 directory...")
add_custom_target(search_executable
		ALL
		DEPENDS ${SEARCH_EXECUTABLE})

add_custom_command(OUTPUT ${COLORING_EXECUTABLE}
		COMMAND make coloring
		WORKING_DIRECTORY ${HW6_DIR}
		VERBATIM
		DEPENDS ${ALL_SOURCE_FILES}
		COMMENT "Running \"make coloring\" in hw6 directory...")
add_custom_target(coloring_executable
		ALL
		DEPENDS ${COLORING_EXECUTABLE})



# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------

add_subdirectory(search_tests)
add_subdirectory(coloring_tests)
add_subdirectory(heap_tests)

set(TEST_TIMEOUT 60) # seconds

# Test target for to generate grade report
add_custom_target(grade
	COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
	COMMAND make clean
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
	COMMAND make testing_utils
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling search via Makefile, output saved to ${COMPILE_LOG_DIR}/search.complog"
	COMMAND make search_executable 1>${COMPILE_LOG_DIR}/search.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling coloring via Makefile, output saved to ${COMPILE_LOG_DIR}/coloring.complog"
	COMMAND make coloring_executable 1>${COMPILE_LOG_DIR}/coloring.complog 2>&1 || true                            
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling heap, output saved to ${COMPILE_LOG_DIR}/heap.complog" # compile test suite instead of actual tests because heap is header-only
	COMMAND make heap_test 1>${COMPILE_LOG_DIR}/heap.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling unit tests"
	COMMAND make search_test || true
	COMMAND make coloring_test || true
	COMMAND make heap_runtime_test || true
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing                                     # remove any old XML logfiles
	COMMAND ${CMAKE_CTEST_COMMAND} -T Test --no-compress-output -C $<CONFIG> --timeout ${TEST_TIMEOUT} || true   # generate XML logfile
	COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
	COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
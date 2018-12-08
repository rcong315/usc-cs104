cmake_minimum_required(VERSION 3.4)

message("########################################################")
message("                 CS104 HW7 Test Suite")
message("########################################################")

project(CS104-HW7-Test-Suite C CXX)

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

if(NOT DEFINED HW7_DIR)

	file(GLOB PARENT_DIR_CPP_FILES "${CMAKE_BINARY_DIR}/../*.h")

	if("${PARENT_DIR_CPP_FILES}" STREQUAL "")
		message(FATAL_ERROR "Cannot find source files in parent directory.  Either move this test directory to your hw7 dir, or run CMake with the \"-DHW7_DIR=<path to hw7>\" argument to use a custom location")
	else()
		get_filename_component(PARENT_DIR_REALPATH "${CMAKE_BINARY_DIR}/.." REALPATH)
		message(STATUS "HW7_DIR autoset to ${PARENT_DIR_REALPATH}")
		set(HW7_DIR ${PARENT_DIR_REALPATH} CACHE PATH "Path to hw7 assignment directory")
	endif()
endif()

# make sure HW7_DIR is an absolute path
get_filename_component(HW7_DIR "${HW7_DIR}" REALPATH)

# build testing utils lib
# ----------------------------------------------------------

add_subdirectory(testing_utils)


# build actual tests
# ----------------------------------------------------------

add_subdirectory(bst_tests)
add_subdirectory(rotate_tests)
add_subdirectory(avl_tests)

set(TEST_TIMEOUT 30) # seconds

# Test target for to generate grade report
add_custom_target(grade
	COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
	COMMAND make clean
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
	COMMAND make testing_utils
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling BST tests, output saved to ${COMPILE_LOG_DIR}/bst.complog" # compile test suite instead of actual tests because all of these problems are header-only
	COMMAND make bst_tests 1>${COMPILE_LOG_DIR}/bst.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling rotateBST tests, output saved to ${COMPILE_LOG_DIR}/rotate.complog"
	COMMAND make rotatebst_tests 1>${COMPILE_LOG_DIR}/rotate.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling AVL BST tests, output saved to ${COMPILE_LOG_DIR}/avl.complog"
	COMMAND make avlbst_tests 1>${COMPILE_LOG_DIR}/avl.complog 2>&1 || true
	COMMAND make avlbst_runtime_tests || true
	COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing                                     # remove any old XML logfiles
	COMMAND ${CMAKE_CTEST_COMMAND} -T Test --no-compress-output -C $<CONFIG> --timeout ${TEST_TIMEOUT} || true   # generate XML logfile
	COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
	COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
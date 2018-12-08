# File for our custom test creation macros


# modified version of gtest_add_test that runs the tests in Valgrind.
# Scans the given executable's sources for GTest tests, then adds them as CTest tests
function(add_valgrind_gtests executable) # ARGN: extra args

    # obtain sources used for building the executable
    get_property(SOURCES_TO_CHECK TARGET ${executable} PROPERTY SOURCES)

    list(REMOVE_DUPLICATES SOURCES_TO_CHECK)

    set(gtest_case_name_regex ".*\\( *([A-Za-z_0-9]+) *, *([A-Za-z_0-9]+) *\\).*")
    set(gtest_test_type_regex "(TYPED_TEST|TEST_?[FP]?)")

    set(NUM_TESTS_FOUND 0)

    foreach(source ${SOURCES_TO_CHECK})

        file(READ "${source}" contents)

        string(REGEX MATCHALL "${gtest_test_type_regex} *\\(([A-Za-z_0-9 ,]+)\\)" found_tests "${contents}")

        foreach(hit ${found_tests})
          string(REGEX MATCH "${gtest_test_type_regex}" test_type ${hit})

          # Parameterized tests have a different signature for the filter
          if("x${test_type}" STREQUAL "xTEST_P")
            string(REGEX REPLACE ${gtest_case_name_regex}  "*/\\1.\\2/*" test_name ${hit})
          elseif("x${test_type}" STREQUAL "xTEST_F" OR "x${test_type}" STREQUAL "xTEST")
            string(REGEX REPLACE ${gtest_case_name_regex} "\\1.\\2" test_name ${hit})
          elseif("x${test_type}" STREQUAL "xTYPED_TEST")
            string(REGEX REPLACE ${gtest_case_name_regex} "\\1/*.\\2" test_name ${hit})
          else()
            message(WARNING "Could not parse GTest ${hit} for adding to CTest.")
            continue()
          endif()

          add_test(NAME ${test_name} COMMAND valgrind ${VALGRIND_ARGS} $<TARGET_FILE:${executable}> --gtest_filter=${test_name} ${ARGN})

          math(EXPR NUM_TESTS_FOUND "${NUM_TESTS_FOUND} + 1")
        endforeach()

    endforeach()

    message(STATUS "Found ${NUM_TESTS_FOUND} GTests from ${executable}")
endfunction()

# custom test target that prints error messages on failure (for some reason it doesn't do this by default???)
# from https://stackoverflow.com/questions/5709914/using-cmake-how-do-i-get-verbose-output-from-ctest
add_custom_target(check 
    COMMAND ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR}          # sean for new source files and tests 
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR}  # force rebuild of changed source files
    COMMAND ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 
        ${CMAKE_CTEST_COMMAND} -C $<CONFIG> -j 2 --timeout 60
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
	
set(COMPILE_LOG_DIR ${CMAKE_BINARY_DIR}/compile-logs)
set(OUTPUT_LOG_DIR ${CMAKE_BINARY_DIR}/test-output)
file(MAKE_DIRECTORY ${COMPILE_LOG_DIR} ${OUTPUT_LOG_DIR})

# write CTest config file to  increase length of saved output for passed tests
file(GENERATE OUTPUT ${CMAKE_BINARY_DIR}/CTestCustom.cmake CONTENT "
set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 307200)
")

# Test target for to generate grade report
add_custom_target(grade 
  COMMAND ${CMAKE_COMMAND} -E echo "-- Cleaning build dir to get a clean record of compilation warnings and errors"
  COMMAND make clean
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling testing tools"
	COMMAND make testing_utils || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling selection sort, output saved to ${COMPILE_LOG_DIR}/selection_sort.complog"
	COMMAND make hw2_selection_sort 1>${COMPILE_LOG_DIR}/selection_sort.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling circular list, output saved to ${COMPILE_LOG_DIR}/circular_list.complog"
	COMMAND make hw2_circular_list 1>${COMPILE_LOG_DIR}/circular_list.complog 2>&1 || true
	COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling duck duck goose, output saved to ${COMPILE_LOG_DIR}/duck_duck_goose.complog"
	COMMAND make hw2_duck_duck_goose 1>${COMPILE_LOG_DIR}/duck_duck_goose.complog 2>&1 || true
    COMMAND ${CMAKE_COMMAND} -E echo "-- Compiling unit tests"
    COMMAND make all || true
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/Testing       # remove any old XML logfiles
    COMMAND ${CMAKE_CTEST_COMMAND} -T Test -C $<CONFIG> --no-compress-output --timeout 60 || true             # generate XML logfile
    COMMAND ${CMAKE_COMMAND} -E echo "-- Generating grade report"
    COMMAND python3 ${CMAKE_SOURCE_DIR}/gen_grade_report.py
   WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
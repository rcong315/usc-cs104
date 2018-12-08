
# make sure that the tests have a directory to put their output files
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/testFiles)

set(DDG_TEST_SOURCES
    basic_tests.cpp
    duck_duck_goose_analyzer.cpp
    duck_duck_goose_utils.cpp
    single_round_test.cpp
    whole_program_test.cpp)

set(DDG_RUNTIME_TEST_SOURCES
    duck_duck_goose_utils.cpp
    duck_duck_goose_runtime.cpp)

# build runtime tests seperately so Valgrind won't be used
add_executable(duck_duck_goose_runtime ${DDG_RUNTIME_TEST_SOURCES})
target_link_libraries(duck_duck_goose_runtime testing_utils hw2_duck_duck_goose hw2_circular_list gtest gtest_main)
gtest_add_tests(duck_duck_goose_runtime "" AUTO)

add_executable(duck_duck_goose_test ${DDG_TEST_SOURCES})
target_link_libraries(duck_duck_goose_test testing_utils hw2_duck_duck_goose hw2_circular_list gtest gtest_main)

add_dependencies(duck_duck_goose_test duck_duck_goose)

add_valgrind_gtests(duck_duck_goose_test)

# tell tests where to find the executable
target_compile_definitions(duck_duck_goose_test PRIVATE DDG_EXECUTABLE=\"$<TARGET_FILE:duck_duck_goose>\")
target_compile_definitions(duck_duck_goose_runtime PRIVATE DDG_EXECUTABLE=\"$<TARGET_FILE:duck_duck_goose>\")

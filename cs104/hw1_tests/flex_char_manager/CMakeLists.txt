
# add all source files in the current source folder as sources
file(GLOB FLEX_CHAR_MANAGER_TEST_SOURCES "*.cpp")

add_executable(flex_char_manager_test ${FLEX_CHAR_MANAGER_TEST_SOURCES})
target_link_libraries(flex_char_manager_test hw1_flex_char_manager hw1_simple_char_manager testing_utils gtest gtest_main)
add_dependencies(flex_char_manager_test second_memtest)

add_valgrind_gtests(flex_char_manager_test)

# add all source files in the current source folder as sources
file(GLOB SIMPLE_CHAR_MANAGER_TEST_SOURCES "*.cpp")

add_executable(simple_char_manager_test ${SIMPLE_CHAR_MANAGER_TEST_SOURCES})
target_link_libraries(simple_char_manager_test hw1_simple_char_manager testing_utils gtest gtest_main)
add_dependencies(simple_char_manager_test first_memtest)

add_valgrind_gtests(simple_char_manager_test)
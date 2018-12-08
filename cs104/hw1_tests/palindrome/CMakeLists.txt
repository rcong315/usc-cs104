# add all source files in the current source folder as sources
file(GLOB PALINDROME_TEST_SOURCES "*.cpp")

add_executable(palindrome_test ${PALINDROME_TEST_SOURCES})
target_link_libraries(palindrome_test testing_utils gtest gtest_main)
add_dependencies(palindrome_test q4_palindrome)

add_valgrind_gtests(palindrome_test)
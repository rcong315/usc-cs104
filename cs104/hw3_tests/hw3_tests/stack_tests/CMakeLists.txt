
# regular test cases
add_executable(stack_test stack_tests.cpp)
target_link_libraries(stack_test hw3_stack testing_utils gtest gtest_main)
add_valgrind_gtests(stack_test)

# runtime test cases (not run in valgrind)
add_executable(stack_runtime_test stack_runtime_tests.cpp)
target_link_libraries(stack_runtime_test hw3_stack testing_utils gtest gtest_main)
gtest_add_tests(stack_runtime_test "" AUTO)

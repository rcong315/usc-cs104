
add_executable(msort_test msort_tests.cpp)
target_link_libraries(msort_test testing_utils hw5_msort gtest gtest_main)

add_executable(msort_runtime_test msort_runtime_tests.cpp)
target_link_libraries(msort_runtime_test testing_utils hw5_msort gtest gtest_main)

add_valgrind_gtests(msort_test)
gtest_add_tests(msort_runtime_test "" AUTO)


add_executable(heap_test heap_tests.cpp)
target_link_libraries(heap_test testing_utils gtest gtest_main)
target_include_directories(heap_test PUBLIC ${HW6_DIR})

add_valgrind_gtests(heap_test)

add_executable(heap_runtime_test heap_runtime_tests.cpp)
target_link_libraries(heap_runtime_test testing_utils gtest gtest_main)
target_include_directories(heap_runtime_test PUBLIC ${HW6_DIR})

gtest_add_tests(heap_runtime_test "" AUTO)


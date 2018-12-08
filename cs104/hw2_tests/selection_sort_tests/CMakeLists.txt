set(SELECTION_SORT_TEST_SOURCES
    selection_sort_utils.cpp
    test_find_min.cpp
    test_selection_sort.cpp
    basic_tests.cpp)

set(SELECTION_SORT_RUNTIME_SOURCES
    selection_sort_utils.cpp
    selection_sort_runtime.cpp)


# build runtime tests seperately so Valgrind won't be used
add_executable(selection_sort_runtime ${SELECTION_SORT_RUNTIME_SOURCES})
target_link_libraries(selection_sort_runtime hw2_selection_sort testing_utils gtest gtest_main)
gtest_add_tests(selection_sort_runtime "" AUTO)

add_executable(selection_sort_test ${SELECTION_SORT_TEST_SOURCES})
target_link_libraries(selection_sort_test hw2_selection_sort testing_utils gtest gtest_main)
add_valgrind_gtests(selection_sort_test)
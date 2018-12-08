
set(AVLBST_TESTS_SOURCES
    test_insert.cpp
    test_remove.cpp
    publicified_avlbst.h
    check_avl.h)

add_executable(avlbst_tests ${AVLBST_TESTS_SOURCES})
target_link_libraries(avlbst_tests gtest gtest_main testing_utils bst_utils)
target_include_directories(avlbst_tests PUBLIC ${HW7_DIR})

add_executable(avlbst_runtime_tests avl_runtime_tests.cpp)
target_link_libraries(avlbst_runtime_tests gtest gtest_main testing_utils bst_utils)
target_include_directories(avlbst_runtime_tests PUBLIC ${HW7_DIR})

add_valgrind_gtests(avlbst_tests)
gtest_add_tests(avlbst_runtime_tests "" AUTO)

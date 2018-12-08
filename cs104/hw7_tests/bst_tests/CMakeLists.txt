
# make a utility library that the other problems' tests can include
add_library(bst_utils INTERFACE)
target_include_directories(bst_utils INTERFACE . ${HW7_DIR})
target_link_libraries(bst_utils INTERFACE testing_utils)


set(BST_TESTS_SOURCES
    test_insert.cpp
    test_remove.cpp
    test_balance.cpp
    check_bst.h
    create_bst.h
    publicified_bst.h)

add_executable(bst_tests ${BST_TESTS_SOURCES})
target_link_libraries(bst_tests gtest gtest_main testing_utils bst_utils)
target_include_directories(bst_tests PUBLIC ${HW7_DIR})

add_valgrind_gtests(bst_tests)

set(ROTATEBST_TESTS_SOURCES
    test_rotate.cpp
    test_same_keys.cpp
    test_transform.cpp
    publicified_rotatebst.h)

add_executable(rotatebst_tests ${ROTATEBST_TESTS_SOURCES})
target_link_libraries(rotatebst_tests gtest gtest_main testing_utils bst_utils)
target_include_directories(rotatebst_tests PUBLIC ${HW7_DIR})

add_valgrind_gtests(rotatebst_tests)
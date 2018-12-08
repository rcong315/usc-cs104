
add_executable(cave_test cave_tests.cpp)
target_link_libraries(cave_test testing_utils gtest gtest_main)
gtest_add_tests(cave_test "" AUTO)

# make sure user code gets remade first
add_dependencies(cave_test cave_executable)
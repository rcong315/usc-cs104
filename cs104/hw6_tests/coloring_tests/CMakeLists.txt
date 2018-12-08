
add_executable(coloring_test coloring_tests.cpp coloring_checker.cpp)
target_link_libraries(coloring_test testing_utils gtest gtest_main)
gtest_add_tests(coloring_test "" AUTO)

# make sure user code gets remade first
add_dependencies(coloring_test coloring_executable)
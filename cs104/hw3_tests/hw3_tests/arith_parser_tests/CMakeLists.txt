
add_executable(parser_test parser_utils.cpp parser_tests.cpp)
target_link_libraries(parser_test testing_utils gtest gtest_main)
gtest_add_tests(parser_test "" AUTO)

# make sure user code gets remade first
add_dependencies(parser_test user_makefile)
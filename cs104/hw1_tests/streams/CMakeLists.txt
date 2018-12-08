# add all source files in the current source folder as sources
file(GLOB STREAMS_TEST_SOURCES "*.cpp")

add_executable(streams_test ${STREAMS_TEST_SOURCES})
target_link_libraries(streams_test testing_utils gtest gtest_main)
add_dependencies(streams_test q5_streams)

add_valgrind_gtests(streams_test)
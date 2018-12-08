//
// Simple Valgrind execution of first_memtest.cpp.
// Just makes sure it exists and is executable.
//

#include <gtest/gtest.h>

#include <user_code_runner.h>

TEST(FirstMemtest, Execution)
{
	std::string executablePath = TEST_BINARY_DIR "/first_memtest";

	UserCodeRunner firstMemtestRunner(TEST_BINARY_DIR, executablePath, {}, true);

	ASSERT_TRUE(firstMemtestRunner.execute());
}
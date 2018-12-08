//
// Simple Valgrind execution of first_memtest.cpp.
// Just makes sure it exists and is executable.
//

#include <gtest/gtest.h>

#include <user_code_runner.h>

TEST(SecondMemtest, Execution)
{
	std::string executablePath = TEST_BINARY_DIR "/second_memtest";

	UserCodeRunner secondMemtestRunner(TEST_BINARY_DIR, executablePath, {}, true);

	ASSERT_TRUE(secondMemtestRunner.execute());
}

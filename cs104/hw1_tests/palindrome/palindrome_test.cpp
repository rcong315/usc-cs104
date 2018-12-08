//
// Tests for Q4 Palindrome
//

#include <user_code_runner.h>
#include <misc_utils.h>
#include <random_generator.h>

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>

#include <gtest/gtest.h>

#include <fstream>

// utility function to run user's palindrome program
testing::AssertionResult runPalindromeProgram(std::string const & testName, std::string const & input, bool & isPalendrome)
{
	// set up file structure
	std::string executablePath = TEST_BINARY_DIR "/q4_palindrome";
	std::string testFolder =  TEST_BINARY_DIR "/palindrome/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string outputFilePath = testFolder + "/output.log";

	// run the program
	UserCodeRunner streamsRunner(testFolder, executablePath, {input}, outputFilePath, true);
	testing::AssertionResult result = streamsRunner.execute();

	if(!result)
	{
		return result;
	}

	// regex to match one alphabetic word without spaces on a line
	kwsys::RegularExpression lineRegex("^[a-zA-Z]+$");

	// read output into vector
	{
		std::ifstream outputFile(outputFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}

		std::string outputLine;
		std::getline(outputFile, outputLine);

		if(outputLine.find("Not a Palindrome") != std::string::npos)
		{
			isPalendrome = false;
		}
		else if(outputLine.find("Palindrome") != std::string::npos)
		{
			isPalendrome = true;
		}
		else
		{
			return testing::AssertionFailure() << "Couldn't find 'palendrome' or 'not a palendrome' result in program output";
		}

		return testing::AssertionSuccess();
	}

};

TEST(Palindrome, Empty)
{
	bool isPalendrome;
	ASSERT_TRUE(runPalindromeProgram("empty", "", isPalendrome));

	ASSERT_TRUE(isPalendrome);
}

TEST(Palindrome, SingleChar)
{
	bool isPalendrome;
	ASSERT_TRUE(runPalindromeProgram("single_char", "r", isPalendrome));

	ASSERT_TRUE(isPalendrome);
}

TEST(Palindrome, PalindromeWordOddLength)
{
	bool isPalendrome;
	ASSERT_TRUE(runPalindromeProgram("palindrome_word_oddlength", "racecar", isPalendrome));

	ASSERT_TRUE(isPalendrome);
}

TEST(Palindrome, PalindromeWordEvenLength)
{
	bool isPalendrome;
	ASSERT_TRUE(runPalindromeProgram("palindrome_word_evenlength", "redder", isPalendrome));

	ASSERT_TRUE(isPalendrome);
}

TEST(Palindrome, NonPalindromeWordOddLength)
{
	bool isPalendrome;
	ASSERT_TRUE(runPalindromeProgram("non_palindrome_word_oddlength", "abcddba", isPalendrome));

	ASSERT_FALSE(isPalendrome);
}

TEST(Palindrome, NonPalindromeWordEvenLength)
{
	bool isPalendrome;
	ASSERT_TRUE(runPalindromeProgram("non_palindrome_word_evenlength", "amanaplanacanal", isPalendrome));

	ASSERT_FALSE(isPalendrome);
}


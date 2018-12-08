//
// Tests for Q5 Streams
//

#include <user_code_runner.h>
#include <misc_utils.h>
#include <random_generator.h>

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>

#include <gtest/gtest.h>

#include <fstream>

// utility function to run user's streams program
testing::AssertionResult runStreamsProgram(std::string const & testName, std::string const & input, std::vector<std::string> & output)
{
	// set up file structure
	std::string executablePath = TEST_BINARY_DIR "/q5_streams";
	std::string testFolder =  TEST_BINARY_DIR "/streams/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.log";

	// create config file
	{
		std::ofstream inputFile(inputFilePath);

		if(!inputFile)
		{
			return testing::AssertionFailure() << "Couldn't create input file " << inputFilePath;
		}

		inputFile << input;
	}

	// run the program
	UserCodeRunner streamsRunner(testFolder, executablePath, {inputFilePath}, outputFilePath, true);
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

		size_t lineNumber = 1;

		while(outputFile)
		{
			std::string outputLine;
			std::getline(outputFile, outputLine);

			// if the file ends with a newline, we will get a final "phantom" 0-length string
			if(outputFile.eof() && outputLine == "")
			{
				break;
			}

			if(!lineRegex.find(outputLine))
			{
				return testing::AssertionFailure() << "Formatting error at output (" << outputFilePath << ") line " << std::dec << lineNumber << ": line did not contain exactly one word";
			}

			output.push_back(outputLine);

			++lineNumber;
		}


		return testing::AssertionSuccess();
	}

};

TEST(Streams, NoWords)
{
	std::vector<std::string> results;
	ASSERT_TRUE(runStreamsProgram("no_words", "0", results));

	ASSERT_TRUE(results.empty());
}

TEST(Streams, OneWord)
{
	std::vector<std::string> results;

	ASSERT_TRUE(runStreamsProgram("one_word", "1\nfoobar", results));

	ASSERT_EQ(results, (std::vector<std::string>{"foobar"}));
}

TEST(Streams, FiveWordsSameLine)
{
	std::vector<std::string> results;

	ASSERT_TRUE(runStreamsProgram("five_words_same_line", "5\nwa puroguramu miteita ni kagami", results));

	ASSERT_EQ(results, (std::vector<std::string>{"kagami", "ni", "miteita", "puroguramu", "wa"}));
}

TEST(Streams, FiveWordsSeparateLines)
{
	std::vector<std::string> results;

	std::stringstream input;
	input << "5" << std::endl;
	input << "recess" << std::endl;
	input << "not" << std::endl;
	input << "is" << std::endl;
	input << "this" << std::endl;
	input << "This" << std::endl;

	ASSERT_TRUE(runStreamsProgram("five_words_separate_lines", input.str(), results));

	ASSERT_EQ(results, (std::vector<std::string>{"This", "this", "is", "not", "recess"})); // <- why is this the test string?  It's the lyrics of the song I was listening to when I wrote this
}

TEST(Streams, MixedWhitespace)
{
	std::vector<std::string> results;

	std::stringstream input;
	input << "6" << std::endl;
	input << "\tZoidberg" << std::endl;
	input << std::endl;
	input << "not\t" << std::endl;
	input << "      why      " << std::endl;
	input << std::endl;
	input << std::endl;
	input << " \t whitespace\t" << std::endl;
	input << " FOR\tlooking" << std::endl;
	input << std::endl;


	ASSERT_TRUE(runStreamsProgram("mixed_whitespace", input.str(), results));

	ASSERT_EQ(results, (std::vector<std::string>{"looking", "FOR", "whitespace", "why", "not", "Zoidberg"}));
}

TEST(Streams, ThousandWordStressTest)
{
	const size_t numWords = 1000;
	const RandomSeed seed = 999995;

	std::vector<std::string> results;

	std::stringstream input;
	input << numWords << std::endl;

	std::vector<std::string> randomWords = makeRandomAlphaStringVector(numWords, seed, 5, true);
	std::vector<std::string> reversedWords(randomWords.rbegin(), randomWords.rend());

	for(size_t index = 0; index < numWords; ++index)
	{
		input << reversedWords[index] << ' ';
	}

	ASSERT_TRUE(runStreamsProgram("thousand_word_stress_test", input.str(), results));

	ASSERT_EQ(results, randomWords);
}

#include "parser_utils.h"

#include <kwsys/SystemTools.hxx>
#include <kwsys/RegularExpression.hxx>

#include <gtest/gtest.h>

#include <fstream>



testing::AssertionResult runParser(std::string const & testName, std::string const & input, std::string & output)
{
	// set up file structure
	std::string executablePath = USER_CODE_DIR "/parser";
	std::string testFolder =  TEST_BINARY_DIR "/arith_parser_tests/test_files/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	// make input file
	{
		std::ofstream inputFile(inputFilePath);
		inputFile << input << std::endl;
	}

	// run the program
	UserCodeRunner streamsRunner(testFolder, executablePath, {inputFilePath}, outputFilePath, true);
	testing::AssertionResult result = streamsRunner.execute();

	if(!result)
	{
		return result;
	}


	// read output into string
	{
		std::ifstream outputFile(outputFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}

		std::getline(outputFile, output);

		return testing::AssertionSuccess();
	}
}


testing::AssertionResult runParser(std::string const & testName, std::vector<std::string> const & input, std::vector<std::string> & output)
{
	// set up file structure
	std::string executablePath = USER_CODE_DIR "/parser";
	std::string testFolder =  TEST_BINARY_DIR "/arith_parser_tests/test_files/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	// make input file
	{
		std::ofstream inputFile(inputFilePath);

		for(std::string const & inputLine : input)
		{
			inputFile << inputLine << std::endl;
		}
	}

	// run the program
	UserCodeRunner streamsRunner(testFolder, executablePath, {inputFilePath}, outputFilePath, true);
	testing::AssertionResult result = streamsRunner.execute();

	if(!result)
	{
		return result;
	}


	// read output into string
	{
		std::ifstream outputFile(outputFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}

		while(outputFile)
		{
			std::string outputLine;
			std::getline(outputFile, outputLine);

			// if the file ends with a newline, we will get a final "phantom" 0-length string
			if(outputFile.eof() && outputLine.empty())
			{
				break;
			}

			output.push_back(outputLine);
		}

		return testing::AssertionSuccess();
	}
}


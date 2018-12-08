//
// CS104 HW6 graph search test suite
//

#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <random_generator.h>
#include <misc_utils.h>

#include <kwsys/SystemTools.hxx>

#include <string>
#include <fstream>

// Tries running the user's search program on the given input, and reports whether the value for the largest country was correct
testing::AssertionResult checkSearch(std::string const & testName, size_t numLetters, size_t expectedLargestCountrySize, std::string const & map, bool useValgrind = true)
{
	// set up file structure
	std::string executablePath = USER_CODE_DIR "/search";
	std::string testFolder =  TEST_BINARY_DIR "/search_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	// convert string literal to a vector of lines
	std::vector<std::string> mapLines = splitString(map, "\n");

	// measure the map string to figure out how big to say the map is
	const size_t mapHeight = mapLines.size();
	const size_t mapWidth = mapLines[0].length();

	std::ofstream inputWriter(inputFilePath);
	inputWriter << numLetters << " " << mapHeight << " " << mapWidth << std::endl;

	for(std::string line : mapLines)
	{
		inputWriter << line << std::endl;

		// check consistency of input
		if(line.size() != mapWidth)
		{
			return testing::AssertionFailure() << "test suite internal error: not all lines of input map are the same length!";
		}
	}

	// run the program
	UserCodeRunner runner(testFolder, executablePath, {inputFilePath}, outputFilePath, useValgrind);
	testing::AssertionResult result = runner.execute();

	if(!result)
	{
		return result;
	}


	// read output into vector
	{
		std::ifstream outputFile(outputFilePath);

		if(!outputFile)
		{
			return testing::AssertionFailure() << "Couldn't open output file " << outputFilePath;
		}

		size_t largestCountrySize;
		outputFile >> largestCountrySize;

		if(largestCountrySize != expectedLargestCountrySize)
		{
			return testing::AssertionFailure() << "Program reported largest country size of " << largestCountrySize << ", but the correct value was " << expectedLargestCountrySize;
		}

	}

	return testing::AssertionSuccess();

};

TEST(Search, OneSquare)
{
	ASSERT_TRUE(checkSearch("OneSquare", 1, 1,
						"A"));
}

TEST(Search, MicroHorizontal)
{
	ASSERT_TRUE(checkSearch("Micro", 2, 2,
						"AA\n"
                        "BB"));
}

TEST(Search, MicroVertical)
{
	ASSERT_TRUE(checkSearch("MicroVertical", 2, 2,
	                        "CD\n"
	                        "CD"));
}

TEST(Search, Discontiguous)
{
	ASSERT_TRUE(checkSearch("Discontiguous", 3, 4,
                        "ACAA\n"
                        "BBAA"));
}

TEST(Search, Ring)
{
	ASSERT_TRUE(checkSearch("Ring", 2, 10,
                        "AAAA\n"
					    "ABBA\n"
					    "AAAA"));
}

TEST(Search, EqualSmallerCountries)
{
	ASSERT_TRUE(checkSearch("EqualSmallerCountries", 3, 4,
	                        "AAAA\n"
	                        "CBBB\n"
	                        "CCAA"));
}

TEST(Search, 26Letters)
{
	ASSERT_TRUE(checkSearch("26Letters", 26, 5,
	                        "ABCDEF\n"
	                        "GHIJKL\n"
	                        "MNOPQR\n"
						    "STUVWX\n"
		                    "YZZZZZ"));
}

TEST(Search, DiagonalCountries)
{
	ASSERT_TRUE(checkSearch("DiagonalCountries", 3, 4,
	                        "AAAR\n"
	                        "ABBB\n"
	                        "RAAA"));
}

TEST(Search, ProvidedMap)
{
	// this one is the map provided on the hw page
	ASSERT_TRUE(checkSearch("ProvidedMap", 3, 21,
	                        "AAAAAABBBBBBB\n"
	                        "AAAAAABBBBBBA\n"
	                        "BBBAAABBBBBAA\n"
	                        "BBAAAABBCCAAA\n"
	                        "BBBBBABACCCAA\n"
						    "BBBBBBAAAAAAA"));
}


TEST(Search, WindingRing)
{
	ASSERT_TRUE(checkSearch("WindingRing", 4, 33,
	                        "AAOOOAOOOBBBB\n"
	                        "AOOAOOOBOOOBA\n"
	                        "BBOAAABBBOOAA\n"
	                        "BOOAAABBCCOAA\n"
	                        "BOOOOOOACOOAA\n"
	                        "BBBBBOOOOOAAA"));
}

TEST(Search, Concentric)
{
	ASSERT_TRUE(checkSearch("Concentric", 3, 41,
	                        "PPPPPPPPPPPP\n"
	                        "PPYYYYYYYYPP\n"
	                        "PXXPPPPPXXPP\n"
						 	"PXXPXXXPXXPP\n"
	                        "PXXPPPPPXXPP\n"
	                        "PPYYYYYYYYPP\n"
	                        "PPPPPPPPPPPP"));
}

TEST(Search, Checkerboard)
{
	ASSERT_TRUE(checkSearch("Checkerboard", 2, 1,
	                        "XYXYXYXYXYXY\n"
	                        "YXYXYXYXYXYX\n"
	                        "XYXYXYXYXYXY\n"
	                        "YXYXYXYXYXYX\n"
	                        "XYXYXYXYXYXY\n"
	                        "YXYXYXYXYXYX\n"
	                        "XYXYXYXYXYXY"));
}
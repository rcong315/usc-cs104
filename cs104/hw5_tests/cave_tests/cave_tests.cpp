// CS104 test file for hw5 cave

#include <gtest/gtest.h>

#include <user_code_runner.h>
#include <random_generator.h>
#include <misc_utils.h>

#include <kwsys/SystemTools.hxx>

#include <string>
#include <fstream>

// Tries running the user's cave program on the given input, and reports whether the program said it was rolled up or not
testing::AssertionResult runCave(std::string const & testName, std::string const & input, bool & isRolledUp, bool useValgrind = true)
{
	// set up file structure
	std::string executablePath = USER_CODE_DIR "/cave";
	std::string testFolder =  TEST_BINARY_DIR "/cave_tests/testFiles/" + testName;
	kwsys::SystemTools::MakeDirectory(testFolder);
	std::string inputFilePath = testFolder + "/input.txt";
	std::string outputFilePath = testFolder + "/output.txt";

	// run the program
	UserCodeRunner runner(testFolder, executablePath, {}, outputFilePath, useValgrind);
	runner.setStdin(input + "\n", inputFilePath);
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

		while(outputFile)
		{
			std::string outputLine;
			std::getline(outputFile, outputLine);
			makeLowercase(outputLine);

			if(outputLine.find("not rolled up") != std::string::npos)
			{
				isRolledUp = false;
				return testing::AssertionSuccess();
			}
			else if(outputLine.find("rolled up") != std::string::npos)
			{
				isRolledUp = true;
				return testing::AssertionSuccess();
			}
		}

	}

	return testing::AssertionFailure() << "Couldn't find 'rolled up' or 'not rolled up' result in program output";

};

TEST(Cave, OneMove)
{
	bool result;
	ASSERT_TRUE(runCave("OneMove", "e", result));
	ASSERT_FALSE(result);
}

TEST(Cave, TwoMoves)
{
	bool result;
	ASSERT_TRUE(runCave("TwoMoves", "ss", result));
	ASSERT_FALSE(result);
}

TEST(Cave, OneTripEW)
{
	bool result;
	ASSERT_TRUE(runCave("OneTripEW", "ew", result));
	ASSERT_TRUE(result);
}

TEST(Cave, OneTripWE)
{
	bool result;
	ASSERT_TRUE(runCave("OneTripWE", "we", result));
	ASSERT_TRUE(result);
}

TEST(Cave, OneTripNS)
{
	bool result;
	ASSERT_TRUE(runCave("OneTripNS", "ns", result));
	ASSERT_TRUE(result);
}

TEST(Cave, SmallLoop)
{
	bool result;
	ASSERT_TRUE(runCave("SmallLoop", "enws", result));
	ASSERT_FALSE(result);
}

TEST(Cave, LargeLoop)
{
	bool result;
	ASSERT_TRUE(runCave("LargeLoop", "eeeennwwwwss", result));
	ASSERT_FALSE(result);
}

TEST(Cave, LoopRetrace)
{
	bool result;
	ASSERT_TRUE(runCave("LoopRetrace", "enwsnesw", result));
	ASSERT_TRUE(result);
}

TEST(Cave, Branching)
{
	bool result;
	ASSERT_TRUE(runCave("Branching", "eeeneesnwwssssewnnnwww", result));
	ASSERT_TRUE(result);
}

TEST(Cave, RightMovesWrongOrder)
{
	bool result;
	ASSERT_TRUE(runCave("Branching", "wwwneese", result));
	ASSERT_FALSE(result);
}


TEST(CaveStress, TenThousandMoves)
{
	const size_t numMoves = 10000;

	std::string path = std::string(numMoves, 'e') + std::string(numMoves, 'w');

	bool result;
	ASSERT_TRUE(runCave("TenThousandMoves", path, result));
	ASSERT_TRUE(result);
}

TEST(CaveStress, RandomMovements)
{
	const size_t numTrials = 50;
	const size_t numMoves = 50;
	const RandomSeed masterSeed = 3798;

	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed currSeed : seeds)
	{
		// generate random vector of the four movement characters
		std::vector<char> moves = makeRandomSequence(numMoves, std::vector<char>{'n', 's', 'e', 'w'}, currSeed);
		bool result;
		ASSERT_TRUE(runCave("RandomMovements", std::string(moves.begin(), moves.end()), result, false));
		ASSERT_FALSE(result);
	}


}

// recursive helper function for LongRandomPath
// generates
std::string genRandomPathHelper(std::string currPath, size_t recursionsLeft, std::vector<size_t> const & randomChoices)
{
	if(recursionsLeft > 0)
	{
		static const std::vector<std::pair<char, char>> directionChoices = {std::make_pair('n', 's'), std::make_pair('s', 'n'), std::make_pair('e', 'w'), std::make_pair('w', 'e')};
		std::pair<char, char> directionChoice = directionChoices.at(randomChoices.at(recursionsLeft - 1));

		return directionChoice.first + genRandomPathHelper(currPath, recursionsLeft - 1, randomChoices) + directionChoice.second;
	}

	return currPath;
}

TEST(CaveStress, RandomCorrectPath)
{
	const size_t numTrials = 50;
	const size_t numMoves = 50;
	const RandomSeed masterSeed = 9999;

	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials, masterSeed);

	for(RandomSeed currSeed : seeds)
	{
		std::vector<size_t> choices = makeRandomNumberVector<size_t>(numTrials, 0, 3, currSeed, true);
		std::string path = genRandomPathHelper("", numMoves, choices);

		std::cout << path << std::endl;

		bool result;
		ASSERT_TRUE(runCave("RandomCorrectPath", path, result, false));
		ASSERT_TRUE(result);
	}


}
#include "duck_duck_goose_analyzer.h"
#include <duck_duck_goose_utils.h>
#include <random_generator.h>

#include <duck_duck_goose.h>

#include <gtest/gtest.h>

#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

TEST(DDGProgram, TwoPlayers)
{
	int itPlayer = 99;
	std::vector<int> otherPlayers = {100};
	std::string output;

	// run four times so as to get all likely outcomes
	for(unsigned int seed = 27; seed < 31; ++seed)
	{
		ASSERT_TRUE(runDuckDuckGooseProgram(seed, itPlayer, otherPlayers, "two_players", output));

		ASSERT_TRUE(checkDDGGameOutput(output, otherPlayers, itPlayer));
	}

}
TEST(DDGProgram, TwentyPlayers)
{
	const unsigned int numPlayers = 20;
	const RandomSeed seed = 28504;

	int itPlayer = 1;
	std::vector<int> otherPlayers = makeRandomNumberVector<int>(numPlayers, 2, numPlayers * 4, seed, false);
	std::string output;

	// run ten times so as to get all likely outcomes
	for(unsigned int seed = 77777; seed < 77787; ++seed)
	{
		ASSERT_TRUE(runDuckDuckGooseProgram(seed, itPlayer, otherPlayers, "twenty_players", output));

		ASSERT_TRUE(checkDDGGameOutput(output, otherPlayers, itPlayer));
	}
}

TEST(DDGProgram, TwoHundredPlayers)
{
	const unsigned int numPlayers = 200;
	const RandomSeed seed = 9001;

	int itPlayer = 1;
	std::vector<int> otherPlayers = makeRandomNumberVector<int>(numPlayers, 2, numPlayers * 4, seed, false);
	std::string output;

	// run two times so as to get all likely outcomes
	for(unsigned int seed = 6490; seed < 6490 + 2; ++seed)
	{
		ASSERT_TRUE(runDuckDuckGooseProgram(seed, itPlayer, otherPlayers, "five_hundred_players", output));

		ASSERT_TRUE(checkDDGGameOutput(output, otherPlayers, itPlayer));
	}
}
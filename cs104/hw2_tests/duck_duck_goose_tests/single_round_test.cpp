//
// Created by cs104 on 8/6/18.
//

#include "duck_duck_goose_analyzer.h"
#include <duck_duck_goose_utils.h>
#include <random_generator.h>

#include <duck_duck_goose.h>

#include <gtest/gtest.h>

#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

// first a simple test with two players
TEST(DDGRound, TwoPlayers)
{
	srand(9);

	GameData testData;
	testData.itPlayerID = 2;
	testData.playerList.push_back(7);

	std::stringstream roundOutput;

	simulateDDGRound(&testData, roundOutput);

	DuckDuckGooseRoundResults analysisResults;
	ASSERT_TRUE(analyzeDDGRoundOutput(roundOutput.str(), {7}, 2, analysisResults));
}

// now let's try with 5 players
TEST(DDGRound, FivePlayers)
{
	srand(9979);

	std::vector<int> players{8, 19, 7, 36};

	GameData testData;
	testData.itPlayerID = 99;
	for(int player : players)
	{
		testData.playerList.push_back(player);
	}

	std::stringstream roundOutput;

	simulateDDGRound(&testData, roundOutput);

	DuckDuckGooseRoundResults analysisResults;
	EXPECT_TRUE(analyzeDDGRoundOutput(roundOutput.str(), players, 99, analysisResults));
}

// runs the same round 10000 times and checks that each player has the same probability of being selected
TEST(DDGRound, GooseSelectionProbability)
{
	const size_t numPlayers = 10;
	const size_t numTrials = 10000;
	const double tolerance = .5;

	std::vector<int> players{10, 20, 30, 40, 50, 60, 70, 80, 90};
	const int itPlayerID = 1000;

	double averageGooseIndex = 0;

	for(size_t trial = 0; trial < numTrials; ++trial)
	{
		srand(static_cast<unsigned int>(trial));

		// build game data
		GameData testData;
		testData.itPlayerID = itPlayerID;
		for(int player : players)
		{
			testData.playerList.push_back(player);
		}

		// run round
		std::stringstream roundOutput;
		simulateDDGRound(&testData, roundOutput);
		DuckDuckGooseRoundResults analysisResults;
		analyzeDDGRoundOutput(roundOutput.str(), players, itPlayerID, analysisResults);

		averageGooseIndex += analysisResults.gooseIndex;
	}

	averageGooseIndex /= numTrials;

	// the goose index is a random number between 0 and 4*(numPlayers-1)-1, so it should be close to the middle of that range
	size_t maxGooseIndex = 4*(numPlayers-1)-1;

	std::cout << "Average goose index: " << std::fixed << std::setprecision(3) << averageGooseIndex << std::endl;
	EXPECT_GE(averageGooseIndex, maxGooseIndex/2.0 - tolerance);
	EXPECT_LE(averageGooseIndex, maxGooseIndex/2.0 + tolerance);

}

// test that the goose and it have the same probability of winning the chase
TEST(DDGRound, ChaseWinningProbability)
{
	const size_t numTrials = 10000;
	const double tolerance = .025;

	std::vector<int> players{24, 96, 384, 768, 1536, 3048};
	const int itPlayerID = 2;

	double averageGooseWinProbability = 0;

	for(size_t trial = 0; trial < numTrials; ++trial)
	{
		srand(static_cast<unsigned int>(trial));

		// build game data
		GameData testData;
		testData.itPlayerID = itPlayerID;
		for(int player : players)
		{
			testData.playerList.push_back(player);
		}

		// run round
		std::stringstream roundOutput;
		simulateDDGRound(&testData, roundOutput);
		DuckDuckGooseRoundResults analysisResults;
		analyzeDDGRoundOutput(roundOutput.str(), players, itPlayerID, analysisResults);

		averageGooseWinProbability += analysisResults.gooseWon ? 1 : 0;
	}

	averageGooseWinProbability /= numTrials;

	std::cout << "Average goose win probability: " << std::fixed << std::setprecision(3) << averageGooseWinProbability << std::endl;
	EXPECT_GE(averageGooseWinProbability, 0.5 - tolerance);
	EXPECT_LE(averageGooseWinProbability, 0.5 + tolerance);

}

// now let's try with hundreds of random players
TEST(DDGRound, RandomStressTest)
{
	const size_t numTrials = 500;
	const size_t numPlayers = 200;
	const RandomSeed origSeed = 99999;

	for(RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<int> players = makeRandomNumberVector<int>(numPlayers, 1, std::numeric_limits<int>::max(), seed, false);

		// take one player to use as it
		int itPlayerID = *players.rbegin();
		players.erase(--players.end());

		// build game data
		GameData testData;
		testData.itPlayerID = itPlayerID;
		for(int player : players)
		{
			testData.playerList.push_back(player);
		}

		// run round
		std::stringstream roundOutput;
		simulateDDGRound(&testData, roundOutput);
		DuckDuckGooseRoundResults analysisResults;
		ASSERT_TRUE(analyzeDDGRoundOutput(roundOutput.str(), players, itPlayerID, analysisResults));
	}
}
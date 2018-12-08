// File for runtime tests for duck duck goose

#include <gtest/gtest.h>

#include <runtime_evaluator.h>
#include <random_generator.h>

#include <duck_duck_goose.h>

// check that the runtime of simulateDDGRound() is linear
TEST(DDGRuntime, DDGRound)
{
	RuntimeEvaluator evaluator("running simulateDDGRound()", 6, 13, 30, [](uint64_t numElements, RandomSeed seed)
	{
		std::vector<int> players = makeRandomNumberVector<int>(numElements, 2, std::numeric_limits<int>::max(), seed, false);
		int itPlayerID = 1; // can't collide with random names because it is less than the min

		// build game data
		GameData testData;
		testData.itPlayerID = itPlayerID;
		for(int player : players)
		{
			testData.playerList.push_back(player);
		}

		std::stringstream roundOutput;

		BenchmarkTimer timer;
		simulateDDGRound(&testData, roundOutput);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.2);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::QUADRATIC));
}
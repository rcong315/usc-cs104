//
// CS104 Fatalist Runtime Tests
//

#include <gtest/gtest.h>

#include <algorithm>

#include <runtime_evaluator.h>
#include <random_generator.h>

// Students aren't required to have a header for fatalist, so we just declare the function in this file.
// We'll get linked to their fatalist.cpp, and if they've done things right the definitions will match up
bool FatalistHypothesis(std::vector<std::pair<int,int> > grades);

TEST(FatalistRuntime, FatalistHypothesis)
{
	RuntimeEvaluator evaluator("FatalistHypothesis()", 1, 15, 40, [&](uint64_t numElements, RandomSeed seed)
	{
		// we don't want the program to early exit, so make sure to fill the entire vector with valid (if uniform) data
		std::vector<std::pair<int, int>> inputData(numElements, std::make_pair(100, 100));

		BenchmarkTimer timer;
		FatalistHypothesis(inputData);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}


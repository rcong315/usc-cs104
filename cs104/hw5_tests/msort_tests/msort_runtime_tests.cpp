//
// CS104 Merge Sort Runtime Tests
//
#include "comparators.h"

#include <msort.h>

#include <gtest/gtest.h>

#include <functional>

#include <runtime_evaluator.h>
#include <random_generator.h>

TEST(MergeSortRuntime, KEqual2)
{
	intCompareLess comparator;

	RuntimeEvaluator evaluator("mergeSort() with k=2", 1, 14, 40, [&](uint64_t numElements, RandomSeed seed)
	{
		std::vector<int> data = makeRandomIntVector(numElements, seed, true);

		BenchmarkTimer timer;
		mergeSort(data, 2, comparator);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEARITHMIC));
}


TEST(MergeSortRuntime, KEqualN)
{
	intCompareLess comparator;

	RuntimeEvaluator evaluator("mergeSort() with k=n", 1, 12, 30, [&](uint64_t numElements, RandomSeed seed)
	{
		std::vector<int> data = makeRandomIntVector(numElements, seed, true);

		BenchmarkTimer timer;
		mergeSort(data, static_cast<int>(numElements), comparator);
		timer.stop();

		return timer.getTime();
	});

	evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::QUADRATIC));
}

//
// CS104 Heap runtime tests
//

#include <MinHeap.h>

#include <gtest/gtest.h>

#include <functional>

#include <runtime_evaluator.h>
#include <random_generator.h>

// dimension of heap to use in these tests
#define D_ARY 2

TEST(HeapRuntime, Add)
{

	RuntimeEvaluator evaluator("MinHeap::add() with d=2", 1, 17, 40, [&](uint64_t numElements, RandomSeed seed)
	{
		MinHeap<int> heap(D_ARY);

		for(int value = 1; value < static_cast<int>(numElements); ++value) // don't add the first element, 0
		{
			heap.add(value, value);
		}

		BenchmarkTimer timer;
		// worst case for MinHeap: add the smallest element
		heap.add(0, 0);
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}

TEST(HeapRuntime, Peek)
{

	RuntimeEvaluator evaluator("MinHeap::peek() with d=2", 1, 17, 40, [&](uint64_t numElements, RandomSeed seed)
	{
		MinHeap<int> heap(D_ARY);

		for(int value = 0; value < static_cast<int>(numElements); ++value)
		{
			heap.add(value, value);
		}

		BenchmarkTimer timer;
		heap.peek();
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(HeapRuntime, Remove)
{

	RuntimeEvaluator evaluator("MinHeap::remove() with d=2", 1, 17, 40, [&](uint64_t numElements, RandomSeed seed)
	{
		MinHeap<int> heap(D_ARY);

		for(int value = 0; value < static_cast<int>(numElements); ++value)
		{
			heap.add(value, value);
		}

		BenchmarkTimer timer;
		heap.remove();
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.4);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LOGARITHMIC));
}
// File for runtime tests for selection sort

#include <gtest/gtest.h>

#include <memory>
#include <iostream>

#include <selection_sort.h>

#include <selection_sort_utils.h>
#include <runtime_evaluator.h>
#include <misc_utils.h>

TEST(SelSortRuntime, FindMin)
{
	// prevent stack overflow from lots of recursion by removing the stack limit
	removeStackLimit();

	RuntimeEvaluator evaluator("using findMin()", 6, 17, 35, [](uint64_t numElements, RandomSeed)
	{
		// create a data vector with the min value at the end (we want the worst-case runtime)
		std::shared_ptr<std::vector<int>> data(std::make_shared<std::vector<int>>());
		for(uint64_t elementsLeft = numElements; elementsLeft > 0; --elementsLeft)
		{
			data->push_back(static_cast<int>(elementsLeft));
		}

		Item* list = makeList(*data);

		BenchmarkTimer timer;
		findMin(list);
		timer.stop();

		deleteList(list);

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.1); // this function runs fast enough that there isn't much variance in the times
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::LINEAR));
}

TEST(SelSortRuntime, SelectionSort)
{
	// prevent stack overflow from lots of recursion by removing the stack limit
	removeStackLimit();

	RuntimeEvaluator evaluator("sorting with LLSelectionSort()", 4, 13, 20, [](uint64_t numElements, RandomSeed)
	{
		// create a data vector in inverse sorted order (we want the worst-case runtime)
		std::shared_ptr<std::vector<int>> data(std::make_shared<std::vector<int>>());
		for(uint64_t elementsLeft = numElements; elementsLeft > 0; --elementsLeft)
		{
			data->push_back(static_cast<int>(elementsLeft));
		}

		Item* list = makeList(*data);

		BenchmarkTimer timer;
		list = LLSelectionSort(list);
		timer.stop();

		deleteList(list);

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::QUADRATIC));
}

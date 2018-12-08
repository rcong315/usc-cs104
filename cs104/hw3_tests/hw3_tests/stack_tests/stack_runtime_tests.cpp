
#include <stackint.h>

#include <gtest/gtest.h>

#include <runtime_evaluator.h>

#include <algorithm>

TEST(StackRuntime, Push)
{
	RuntimeEvaluator evaluator("using push()", 1, 20, 45, [](uint64_t numElements, RandomSeed)
	{
		StackInt stack;

		// push numElements - 1 elements onto the stack
		for(uint64_t counter = 0; counter < numElements - 1; ++counter)
		{
			stack.push(static_cast<const int &>(counter));
		}

		BenchmarkTimer timer;
		for(int counter = 0; counter < 100; ++counter)
		{
			stack.push(static_cast<int>(numElements - 1));
		}
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.2);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(StackRuntime, Pop)
{
	RuntimeEvaluator evaluator("using pop()", 1, 20, 45, [](uint64_t numElements, RandomSeed)
	{
		StackInt stack;

		// push numElements elements onto the stack
		for(uint64_t counter = 0; counter < numElements; ++counter)
		{
			stack.push(static_cast<const int &>(counter));
		}

		BenchmarkTimer timer;
		stack.pop();
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.2);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}

TEST(StackRuntime, Top)
{
	RuntimeEvaluator evaluator("using top()", 1, 20, 45, [](uint64_t numElements, RandomSeed)
	{
		StackInt stack;

		// push numElements elements onto the stack
		for(uint64_t counter = 0; counter < numElements; ++counter)
		{
			stack.push(static_cast<const int &>(counter));
		}

		BenchmarkTimer timer;
		for(int counter = 0; counter < 100; ++counter)
		{
			stack.top();
		}
		timer.stop();

		return timer.getTime();
	});

	//evaluator.enableDebugging();
	evaluator.setCorrelationThreshold(1.2);
	evaluator.evaluate();

	EXPECT_TRUE(evaluator.meetsComplexity(RuntimeEvaluator::TimeComplexity::CONSTANT));
}
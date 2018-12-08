
#include <stackint.h>

#include <gtest/gtest.h>

#include <random_generator.h>

TEST(Stack, ConstructionDestruction)
{
	StackInt stack;
}

TEST(Stack, ZeroElements)
{
	StackInt stack;

	EXPECT_TRUE(stack.empty());
}

TEST(Stack, OneElementAdd)
{
	StackInt stack;

	stack.push(3);

	EXPECT_EQ(3, stack.top());
}

TEST(Stack, OneElementRemove)
{
	StackInt stack;

	stack.push(3);

	EXPECT_EQ(3, stack.top());
	EXPECT_FALSE(stack.empty());

	stack.pop();

	EXPECT_TRUE(stack.empty());
}

TEST(Stack, ThreeElementAddRemove)
{
	StackInt stack;

	stack.push(3);
	stack.push(8);
	stack.push(-9996);

	EXPECT_EQ(-9996, stack.top());

	stack.pop();
	EXPECT_EQ(8, stack.top());

	stack.pop();
	EXPECT_EQ(3, stack.top());
}

/**
* Function used for testing the order of elements within a stack. Gives
* access to member data as well as test macros needed for testing. Inserts
* the given number of elements into the stack and then removes elements
* from the stack until empty, checking the elements while removing. A
* final check is done to make sure the stack is empty at the end.
*/
void stressTestStack(const size_t numElements, RandomSeed seed)
{
	StackInt stack;

	std::vector<int> contents(makeRandomIntVector(numElements, seed, false));

	// first insert contents
	for(auto contentsIter = contents.begin(); contentsIter != contents.end(); ++contentsIter)
	{
		stack.push(*contentsIter);
	}

	// now check them
	for(auto contentsRevIter = contents.rbegin(); contentsRevIter != contents.rend(); ++contentsRevIter)
	{
		ASSERT_EQ(*contentsRevIter, stack.top());
		stack.pop();
	}

	ASSERT_TRUE(stack.empty());
}

TEST(Stack, 10EleStressTest)
{
	ASSERT_NO_FATAL_FAILURE(stressTestStack(10, 6780));
}

TEST(Stack, 500EleStressTest)
{
	ASSERT_NO_FATAL_FAILURE(stressTestStack(500, 3));
}

TEST(Stack, 10000EleStressTest)
{
	ASSERT_NO_FATAL_FAILURE(stressTestStack(10000, 796));
}
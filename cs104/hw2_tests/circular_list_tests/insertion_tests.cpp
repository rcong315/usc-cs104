#include <gtest/gtest.h>

#include <circular_list_int.h>

#include <circular_list_utils.h>
#include <random_generator.h>

#include <limits>

// ----------------------------------------
// CS104 HW2 Problem 2 tests for push_back()
// and index-based traversal
// ----------------------------------------

TEST(ListInsert, NoElements)
{
	CircularListInt list;

	EXPECT_TRUE(list.empty());
	EXPECT_EQ(0, list.size());
	EXPECT_EQ(0, list.get(0));
	EXPECT_EQ(0, list.get(20000));
}

TEST(ListInsert, IntMax)
{
	CircularListInt list;

	list.push_back(std::numeric_limits<int>::max());

	EXPECT_EQ(1, list.size());
	EXPECT_EQ(std::numeric_limits<int>::max(), list.get(0));
}

TEST(ListInsert, IntMin)
{
	CircularListInt list;

	list.push_back(std::numeric_limits<int>::min());

	EXPECT_EQ(1, list.size());
	EXPECT_EQ(std::numeric_limits<int>::min(), list.get(0));
}

TEST(ListInsert, ThreeElements)
{
	std::vector<int> contents{700, 9, 114};

	CircularListInt * list = makeCircularList(contents);

	EXPECT_FALSE(list->empty());
	EXPECT_EQ(3, list->size());
	
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}

TEST(ListInsert, 50RandomElements)
{
	const size_t numElements = 50;
	const size_t numTrials = 30;
	const RandomSeed origSeed = 70; 

	// generate list of random seeds and iterate through them
	for(RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<int> contents(makeRandomIntVector(numElements, seed, false));

		CircularListInt * list = makeCircularList(contents);
		
		EXPECT_TRUE(checkListContent(list, contents));

		delete list;
	}

}

TEST(ListInsert, WrapAround_50RandomElements)
{
	const size_t numElements = 50;
	const size_t numTrials = 30;
	const size_t timesToWrap = 4;
	const RandomSeed origSeed = 80; 

	// generate list of random seeds and iterate through them
	for(RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<int> contents(makeRandomIntVector(numElements, seed, false));

		CircularListInt * list = makeCircularList(contents);
		
		for(size_t circularIndex = 0; circularIndex < timesToWrap * numElements; ++circularIndex)
		{	
			size_t actualIndex = circularIndex % numElements;

			EXPECT_EQ(list->get(circularIndex), contents[actualIndex]);
		}

		delete list;
	}

}


TEST(ListInsert, 10000RandomElements)
{
	const size_t numElements = 10000;
	const size_t numTrials = 2;
	const RandomSeed origSeed = 795; 

	// generate list of random seeds and iterate through them
	for(RandomSeed seed : makeRandomSeedVector(numTrials, origSeed))
	{
		std::vector<int> contents(makeRandomIntVector(numElements, seed, false));

		CircularListInt * list = makeCircularList(contents);
		
		EXPECT_TRUE(checkListContent(list, contents));

		delete list;
	}

}
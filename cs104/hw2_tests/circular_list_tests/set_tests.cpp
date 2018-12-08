#include <gtest/gtest.h>

#include <circular_list_int.h>

#include <circular_list_utils.h>
#include <random_generator.h>

// ----------------------------------------
// CS104 HW2 Problem 2 tests for set()
// ----------------------------------------

TEST(ListSet, ZeroElementSet)
{
	CircularListInt list;

	// should do nothing
	list.set(995, 99999);
	list.set(3, 7);

	EXPECT_EQ(0, list.size());
	EXPECT_EQ(true, list.empty());
}

TEST(ListSet, Head3Elements)
{
	std::vector<int> contents{128, 256, 512};
	CircularListInt * list = makeCircularList(contents);

	list->set(0, 64);

	contents[0] = 64;
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}

TEST(ListSet, Middle3Elements)
{
	std::vector<int> contents{128, 256, 512};
	CircularListInt * list = makeCircularList(contents);

	list->set(1, 384);

	contents[1] = 384;
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}

TEST(ListSet, Tail3Elements)
{
	std::vector<int> contents{128, 256, 512};
	CircularListInt * list = makeCircularList(contents);

	list->set(2, 768);

	contents[2] = 768;
	EXPECT_TRUE(checkListContent(list, contents));

	delete list;
}

TEST(ListSet, ThreeElementsWraparound)
{
	std::vector<int> contents{128, 256, 512};
	CircularListInt * list = makeCircularList(contents);

	for(size_t counter = 0; counter < contents.size(); ++counter)
	{
		list->remove(list->size());
		contents.erase(contents.begin());
		EXPECT_TRUE(checkListContent(list, contents));
	}

	delete list;
}

TEST(ListSet, 50RandomElements)
{
	const size_t numElements = 50;
	const RandomSeed oldContentsSeed = 773;
	const RandomSeed newContentsSeed = 773;

	std::vector<int> oldContents(makeRandomIntVector(numElements, oldContentsSeed, false));
	std::vector<int> newContents(makeRandomIntVector(numElements, newContentsSeed, false));

	CircularListInt * list = makeCircularList(oldContents);

	for(size_t index = 0; index < numElements; ++index)
	{
		list->set(index, newContents[index]);
		oldContents[index] = newContents[index];

		EXPECT_TRUE(checkListContent(list, oldContents));
	}

	delete list;

}
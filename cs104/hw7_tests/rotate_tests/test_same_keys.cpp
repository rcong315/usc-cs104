#include "publicified_rotatebst.h"
#include <check_bst.h>
#include <create_bst.h>

#include <gtest/gtest.h>

TEST(SameKeys, Empty)
{
	rotateBST<int, long> tree1, tree2;

	EXPECT_TRUE(tree1.sameKeys(tree2));
}

TEST(SameKeys, JustRoot)
{
	rotateBST<int, int> tree1, tree2;

	tree1.insert(std::make_pair(1, 4));

	tree2.insert(std::make_pair(1, 4));

	EXPECT_TRUE(tree1.sameKeys(tree2));
}

TEST(SameKeys, SameOrder)
{
	rotateBST<int, int> tree1, tree2;

	tree1.insert(std::make_pair(1, 4));
	tree1.insert(std::make_pair(2, 7));
	tree1.insert(std::make_pair(3, -55));

	tree2.insert(std::make_pair(1, 8));
	tree2.insert(std::make_pair(2, 0));
	tree2.insert(std::make_pair(3, 9999));

	EXPECT_TRUE(tree1.sameKeys(tree2));
}

TEST(SameKeys, DifferentOrder)
{
	rotateBST<char, int> tree1, tree2;

	tree1.insert(std::make_pair('c', 4));
	tree1.insert(std::make_pair('a', 7));
	tree1.insert(std::make_pair('b', -55));

	tree2.insert(std::make_pair('a', 8));
	tree2.insert(std::make_pair('b', 0));
	tree2.insert(std::make_pair('c', 9999));

	EXPECT_TRUE(tree1.sameKeys(tree2));
}

TEST(SameKeys, DifferentKeys)
{
	rotateBST<char, std::string> tree1, tree2;

	tree1.insert(std::make_pair('c', ""));
	tree1.insert(std::make_pair('a', "\0"));
	tree1.insert(std::make_pair('d', "argle"));

	tree2.insert(std::make_pair('b', "blarg"));
	tree2.insert(std::make_pair('a', "bluh"));
	tree2.insert(std::make_pair('t', "gork"));

	EXPECT_FALSE(tree1.sameKeys(tree2));
}

TEST(SameKeys, MissingKey)
{
	rotateBST<char, int> tree1, tree2;

	tree1.insert(std::make_pair('c', 4));
	tree1.insert(std::make_pair('a', 7));
	tree1.insert(std::make_pair('b', -55));
	tree1.insert(std::make_pair('o', -55));

	tree2.insert(std::make_pair('a', 8));
	tree2.insert(std::make_pair('b', 0));
	tree2.insert(std::make_pair('c', 9999));

	EXPECT_FALSE(tree1.sameKeys(tree2));
}


TEST(SameKeys, SameRandom50x30ele)
{
	const RandomSeed masterSeed = 785;
	const size_t numElements = 30;
	const size_t numTrials = 50;

	rotateBST<int, int> testTree1, testTree2;

	// generate 3x as many seeds as trials because we need 3 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 3, masterSeed);

	for(size_t counter = 0; counter < numTrials*3; counter+= 3)
	{
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));

		// fill with the same data, but in different random orders
		fillTree(testTree1, randomData, seeds.at(counter + 1));
		fillTree(testTree2, randomData, seeds.at(counter + 2));

		EXPECT_TRUE(testTree1.sameKeys(testTree2));

		testTree1.clear();
		testTree2.clear();
	}


}

TEST(SameKeys, DifferentRandom50x30ele)
{
	const RandomSeed masterSeed = 349;
	const size_t numElements = 30;
	const size_t numTrials = 50;

	rotateBST<int, int> testTree1, testTree2;

	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 4, masterSeed);

	for(size_t counter = 0; counter < numTrials*4; counter+= 4)
	{
		std::set<int> randomData1 = makeRandomIntSet(numElements, seeds.at(counter));

		// keep generating a new random set until it is different from randomData1
		std::set<int> randomData2;
		for(RandomSeed seedOffset = 0; seedOffset == 0 || randomData1 == randomData2; ++seedOffset)
		{
			randomData2 = makeRandomIntSet(30, seeds.at(counter + 1) + seedOffset);
		}

		fillTree(testTree1, randomData1, seeds.at(counter + 2));
		fillTree(testTree2, randomData2, seeds.at(counter + 3));

		EXPECT_FALSE(testTree1.sameKeys(testTree2));

		testTree1.clear();
		testTree2.clear();
	}


}
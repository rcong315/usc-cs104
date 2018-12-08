#include "publicified_rotatebst.h"
#include <check_bst.h>
#include <create_bst.h>

#include <gtest/gtest.h>

// tests rotateBST::transform().
// Verifies that one BST can be transform()ed into another,
// for simple, corner, and random cases.

TEST(Transform, Empty)
{
	rotateBST<std::string, int> tree1, tree2;

	tree1.transform(tree2);

	EXPECT_TRUE(verifyBST(tree1));
	EXPECT_TRUE(verifyBST(tree2));

	EXPECT_TRUE(checkSameStructure(tree1, tree2));
}


TEST(Transform, OneElement)
{
	rotateBST<int, int> tree1, tree2;

	tree1.insert(std::make_pair(1, 4));

	tree2.insert(std::make_pair(1, 4));

	tree1.transform(tree2);

	EXPECT_TRUE(verifyBST(tree1));
	EXPECT_TRUE(verifyBST(tree2));
	EXPECT_TRUE(checkSameStructure(tree1, tree2));
}

// test where nodes are already in a right-side linked list
TEST(Transform, AlreadyLL)
{
	rotateBST<int, int> tree1, tree2;

	tree1.insert(std::make_pair(1, 4));
	tree1.insert(std::make_pair(2, 7));
	tree1.insert(std::make_pair(3, -55));

	tree2.insert(std::make_pair(1, 8));
	tree2.insert(std::make_pair(2, 0));
	tree2.insert(std::make_pair(3, 9999));

	tree1.transform(tree2);

	EXPECT_TRUE(verifyBST(tree1));
	EXPECT_TRUE(verifyBST(tree2));
	EXPECT_TRUE(checkSameStructure(tree1, tree2));
}

TEST(Transform, DifferentTrees)
{
	rotateBST<int, int> tree1, tree2;

	tree1.insert(std::make_pair(1, 4));
	tree1.insert(std::make_pair(2, 7));
	tree1.insert(std::make_pair(3, -55));

	tree2.insert(std::make_pair(7, 8));
	tree2.insert(std::make_pair(9, 0));
	tree2.insert(std::make_pair(38, 9999));

	tree1.transform(tree2);

	// make sure that neither tree has been modified
	EXPECT_TRUE(verifyBST(tree1, std::set<int>{1, 2, 3}));
	EXPECT_TRUE(verifyBST(tree2, std::set<int>{7, 9, 38}));
}



// test where nodes are already in a left-side linked list
TEST(Transform, AlreadyBackwardsLL)
{
	rotateBST<int, int> tree1, tree2;

	tree1.insert(std::make_pair(3, 4));
	tree1.insert(std::make_pair(2, 7));
	tree1.insert(std::make_pair(1, -55));

	tree2.insert(std::make_pair(3, 8));
	tree2.insert(std::make_pair(2, 0));
	tree2.insert(std::make_pair(1, 9999));

	tree1.transform(tree2);

	ASSERT_TRUE(verifyBST(tree1));
	ASSERT_TRUE(verifyBST(tree2));
	EXPECT_TRUE(checkSameStructure(tree1, tree2));
}

TEST(Transform, BasicTree)
{
	rotateBST<int, int> tree1, tree2;

	tree1.insert(std::make_pair(2, 7));
	tree1.insert(std::make_pair(3, 4));
	tree1.insert(std::make_pair(1, -55));
	tree1.insert(std::make_pair(-10, -3));
	tree1.insert(std::make_pair(4, 97));

	tree2.insert(std::make_pair(3, 4));
	tree2.insert(std::make_pair(1, -55));
	tree2.insert(std::make_pair(2, 7));
	tree2.insert(std::make_pair(-10, -3));
	tree2.insert(std::make_pair(4, 97));

	tree1.transform(tree2);

	ASSERT_TRUE(verifyBST(tree1));
	ASSERT_TRUE(verifyBST(tree2));
	EXPECT_TRUE(checkSameStructure(tree1, tree2));
}

TEST(Transform, Random50x30ele)
{
	const RandomSeed masterSeed = 651;
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

		testTree1.transform(testTree2);

		ASSERT_TRUE(verifyBST(testTree1, randomData));
		ASSERT_TRUE(verifyBST(testTree2, randomData));

		EXPECT_TRUE(checkSameStructure(testTree1, testTree2));

		testTree1.clear();
		testTree2.clear();
	}


}

TEST(Transform, Random3x5000ele)
{
	const RandomSeed masterSeed = 7849;
	const size_t numElements = 5000;
	const size_t numTrials = 3;

	rotateBST<int, int> testTree1, testTree2;

	// generate 3x as many seeds as trials because we need 3 for each trial
	std::vector<RandomSeed> seeds = makeRandomSeedVector(numTrials * 3, masterSeed);

	for(size_t counter = 0; counter < numTrials*3; counter+= 3)
	{
		std::set<int> randomData = makeRandomIntSet(numElements, seeds.at(counter));

		// fill with the same data, but in different random orders
		fillTree(testTree1, randomData, seeds.at(counter + 1));
		fillTree(testTree2, randomData, seeds.at(counter + 2));

		testTree1.transform(testTree2);

		ASSERT_TRUE(verifyBST(testTree1, randomData));
		ASSERT_TRUE(verifyBST(testTree2, randomData));

		EXPECT_TRUE(checkSameStructure(testTree1, testTree2));

		testTree1.clear();
		testTree2.clear();
	}

}

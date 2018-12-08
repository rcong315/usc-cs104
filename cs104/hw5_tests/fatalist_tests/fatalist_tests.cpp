//
// CS104 Fatalist test suite
//

#include <cmath>

#include <gtest/gtest.h>

// Students aren't required to have a header for fatalist, so we just declare the function in this file.
// We'll get linked to their fatalist.cpp, and if they've done things right the definitions will match up
bool FatalistHypothesis(std::vector<std::pair<int,int> > grades);


TEST(Fatalist, OneStudent)
{
	// the hypothesis should always be true with one student
	EXPECT_TRUE(FatalistHypothesis(std::vector<std::pair<int,int>>{{0, 0}}));
	EXPECT_TRUE(FatalistHypothesis(std::vector<std::pair<int,int>>{{99, 99}}));
}

TEST(Fatalist, AllEqual)
{
	ASSERT_TRUE(FatalistHypothesis(std::vector<std::pair<int,int>>{{85, 85}, {85, 85}, {85, 85}}));
}

TEST(Fatalist, Higher170Grade)
{
	ASSERT_TRUE(FatalistHypothesis(std::vector<std::pair<int,int>>{{90, 90}, {90, 85}}));
}

TEST(Fatalist, Higher104Grade)
{
	ASSERT_TRUE(FatalistHypothesis(std::vector<std::pair<int,int>>{{90, 90}, {85, 90}}));
}

TEST(Fatalist, BothGradesHigher)
{
	ASSERT_TRUE(FatalistHypothesis(std::vector<std::pair<int,int>>{{100, 90}, {70, 85}}));
}

TEST(Fatalist, NonConformantData)
{
	ASSERT_FALSE(FatalistHypothesis(std::vector<std::pair<int,int>>{{100, 90}, {70, 92}}));
}

TEST(Fatalist, LargerConformantGroup)
{
	ASSERT_TRUE(FatalistHypothesis(std::vector<std::pair<int,int>>{{100, 94}, {70, 70}, {88, 88}, {70, 88}, {100, 90}}));
}

TEST(Fatalist, LargerNonConformantGroup)
{
	ASSERT_FALSE(FatalistHypothesis(std::vector<std::pair<int,int>>{{99, 94}, {70, 70}, {88, 88}, {70, 88}, {100, 90}}));
}

TEST(Fatalist, VeryNonConformantGroup)
{
	ASSERT_FALSE(FatalistHypothesis(std::vector<std::pair<int,int>>{{99, 70}, {70, 99}, {88, 90}, {70, 88}, {100, 88}}));
}

TEST(FatalistStress, ConformantGroup)
{
	std::vector<std::pair<int, int>> inputData;

	// fill InputData with pairs where one or the other grade increases each time
	for(int index = 0; index < 200; index++)
	{
		int cs104Grade = static_cast<int>(floor(index / 2.0));
		int cs170Grade = static_cast<int>(ceil(index / 2.0));
		inputData.emplace_back(cs104Grade, cs170Grade);
	}

	ASSERT_TRUE(FatalistHypothesis(inputData));
}

TEST(FatalistStress, NonConformantGroup)
{
	std::vector<std::pair<int, int>> inputData;

	for(int index = 0; index < 200; index++)
	{
		int cs104Grade = static_cast<int>(floor(index / 2.0));
		int cs170Grade = 100 - static_cast<int>(ceil(index / 2.0));
		inputData.emplace_back(cs104Grade, cs170Grade);
	}

	ASSERT_FALSE(FatalistHypothesis(inputData));
}
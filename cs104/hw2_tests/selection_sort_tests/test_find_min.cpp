#include <gtest/gtest.h>

#include <selection_sort.h>

#include <selection_sort_utils.h>

#include <algorithm>

#include <limits>
// Tests for hw2's findMin() function

const int LARGE_TEST_SIZE = 100;
const int STRESS_TEST_SIZE = 1000;

bool checkFindMin(std::vector<int>& contents) {
  Item* list = makeList(contents);
  Item* minItem = findMin(list);
  
  std::vector<int>::iterator minItr = std::min_element(std::begin(contents), std::end(contents));
  bool result = (minItr == contents.end() && !minItem) || *minItr == minItem->getValue();
  
  deleteList(list);
  
  return result;
}

TEST(FindMin, 01_NullList)
{
  Item* result = findMin(nullptr);
  EXPECT_EQ(nullptr, result);
}

TEST(FindMin, 02_OneElement)
{
  std::vector<int> contents {0};
  EXPECT_TRUE(checkFindMin(contents));
}

TEST(FindMin, 03_ThreeElements)
{
  std::vector<std::vector<int>> tests
  {
    {0, 1, 2},
    {0, 2, 1},
    {1, 0, 2},
    {1, 2, 0},
    {2, 0, 1},
    {2, 1, 0},
  };

  for (auto& contents : tests) {
    EXPECT_TRUE(checkFindMin(contents));
  }
}

TEST(FindMin, 04_Uniform)
{
  std::vector<int> contents {1, 1};
  EXPECT_TRUE(checkFindMin(contents));
}

TEST(FindMin, 05_UniformLarge)
{
  std::vector<int> contents(LARGE_TEST_SIZE, 1);
  EXPECT_TRUE(checkFindMin(contents));
}

TEST(FindMin, 06_AlternatingElements)
{
  std::vector<int> contents;
  contents.reserve(LARGE_TEST_SIZE);
  for (int i = 0; i < LARGE_TEST_SIZE; ++i)
  {
    contents[i] = i % 2;
  }
  EXPECT_TRUE(checkFindMin(contents));
}

TEST(FindMin, 07_Descending)
{
  std::vector<int> contents;
  for (int i = LARGE_TEST_SIZE; i > 0; --i) {
    contents.emplace_back(i);
  }
  EXPECT_TRUE(checkFindMin(contents));
}

TEST(FindMin, 08_Ascending)
{
  std::vector<int> contents;
  for (int i = 0; i < LARGE_TEST_SIZE; ++i) {
    contents.emplace_back(i);
  }
  EXPECT_TRUE(checkFindMin(contents));
}

TEST(FindMin, 09_ExtremeValues)
{
  std::vector<int> contents(LARGE_TEST_SIZE, std::numeric_limits<int>::min());
  EXPECT_TRUE(checkFindMin(contents));

  contents = std::vector<int>(LARGE_TEST_SIZE, std::numeric_limits<int>::max());
  EXPECT_TRUE(checkFindMin(contents));

  for (int i = 0; i < LARGE_TEST_SIZE; ++i) {
    contents.at(i) = i % 2 ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
  }
  EXPECT_TRUE(checkFindMin(contents));
}

#include <gtest/gtest.h>

#include <selection_sort.h>

#include <selection_sort_utils.h>

#include <algorithm>

#include <limits>
// Tests for hw2's findMin() function

const int LARGE_TEST_SIZE = 100;
const int STRESS_TEST_SIZE = 1000;

bool checkSelectionSort(std::vector<int> &contents)
{
  Item *list = makeList(contents);
  list = LLSelectionSort(list);
  bool result = checkValidPointers(list, contents.size()) && checkSameValues(list, contents) && checkIsSorted(list);
  deleteList(list);
  return result;
}

TEST(SelectionSort, 01_NullList)
{
  Item *result = LLSelectionSort(nullptr);
  EXPECT_EQ(nullptr, result);
}

TEST(SelectionSort, 02_TwoElements)
{
  std::vector<std::vector<int>> tests{{0, 1}, {1, 0}};
  for (auto &test : tests)
  {
    EXPECT_TRUE(checkSelectionSort(test));
  }
}

TEST(SelectionSort, 03_Ascending)
{
  std::vector<int> test;
  for (int i = 0; i < LARGE_TEST_SIZE; ++i)
  {
    test.emplace_back(i);
  }

  EXPECT_TRUE(checkSelectionSort(test));
}

TEST(SelectionSort, 04_Descending)
{
  std::vector<int> test;
  for (int i = LARGE_TEST_SIZE; i > 0; --i)
  {
    test.emplace_back(i);
  }

  EXPECT_TRUE(checkSelectionSort(test));
}

TEST(SelectionSort, 05_Uniform)
{
  std::vector<int> test(LARGE_TEST_SIZE, 0);
  EXPECT_TRUE(checkSelectionSort(test));
}

TEST(SelectionSort, 06_Repeating)
{
  std::vector<int> test;
  for (int i = 0; i < LARGE_TEST_SIZE; ++i)
  {
    test.emplace_back(i % 4);
  }
  EXPECT_TRUE(checkSelectionSort(test));
}

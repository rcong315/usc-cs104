#include "gtest/gtest.h"
#include "../hashtables.h"

#include <vector>
#include <iostream>
#include <string>

using namespace std;

TEST(AnagramTest, IsAnagram1) {
    string str1 = "listen";
    string str2 = "silent";

    EXPECT_TRUE(isAnagram(str1, str2));
}

TEST(AnagramTest, IsAnagram2) {
    //A Decimal Point = I'm a Dot in Place
    string str1 = "A Decimal Point";
    string str2 = "I'm a Dot in Place";

    EXPECT_TRUE(isAnagram(str1, str2));
}

TEST(AnagramTest, IsAnagram3) {
    //A domesticated animal = Docile, as a man tamed it
    string str1 = "A domesticated animal";
    string str2 = "Docile, as a man tamed it";

    EXPECT_TRUE(isAnagram(str1, str2));
}

TEST(AnagramTest, IsNotAnagram1) {
    string str1 = "puzzling";
    string str2 = "unpuzzle";

    EXPECT_FALSE(isAnagram(str1, str2));
}

TEST(AnagramTest, IsNotAnagram2) {
    string str1 = "USC";
    string str2 = "uClA";

    EXPECT_FALSE(isAnagram(str1, str2));
}

TEST(AnagramTest, IsNotAnagram3) {
    string str1 = "Professor Cote";
    string str2 = "Professor Batista";

    EXPECT_FALSE(isAnagram(str1, str2));
}

bool comparePairs(pair<int, int> one, pair<int, int> two) {
    if( (one.first == two.first && one.second == two.second) ||
        (one.second == two.first && one.first == two.second) )
        return true;
    return false;
}

TEST(TwoSumTest, ValidTargetTest1) {
    vector<int> input = {4, 5, 1, 8};
    int target = 6;
    pair<int, int> output(1, 2);

    EXPECT_TRUE(comparePairs(output, twoSum(input, target)));
}

TEST(TwoSumTest, ValidTargetTest2) {
    vector<int> input = {1, 4, 45, 6, 10, -8};
    int target = 16;
    pair<int, int> output(3, 4);

    EXPECT_TRUE(comparePairs(output, twoSum(input, target)));
}

TEST(TwoSumTest, ValidTargetTest3) {
    vector<int> input = {200, 6, 32, -50, 13, 76, 3, 64};
    int target = -44;
    pair<int, int> output(1, 3);

    EXPECT_TRUE(comparePairs(output, twoSum(input, target)));
}

TEST(TwoSumTest, InvalidTargetTest1) {
    vector<int> input = {200, 6, 32, -50, 13, 76, 3, 64};
    int target = 99999;
    pair<int, int> output(-1, -1);

    EXPECT_TRUE(comparePairs(output, twoSum(input, target)));
}

TEST(TwoSumTest, InvalidTargetTest2) {
    vector<int> input = {4, 5, 1, 8};
    int target = 100;
    pair<int, int> output(-1, -1);

    EXPECT_TRUE(comparePairs(output, twoSum(input, target)));
}
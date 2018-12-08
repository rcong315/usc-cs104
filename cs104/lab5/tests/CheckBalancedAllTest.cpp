#include "gtest/gtest.h"
#include "../CheckBalanced.h"
#include <string>

TEST(CheckBalancedAllTest, TestTrue1) 
{
	EXPECT_TRUE(CheckBalancedAll("[()]{}{[()()]()}"));
}

TEST(CheckBalancedAllTest, TestTrue2) 
{
	EXPECT_TRUE(CheckBalancedAll("{[()]}"));
}

TEST(CheckBalancedAllTest, TestTrue3) 
{
	EXPECT_TRUE(CheckBalancedAll("{{}[][()]}"));
}

TEST(CheckBalancedAllTest, TestFalse1) 
{
	EXPECT_FALSE(CheckBalancedAll("[(])"));
}

TEST(CheckBalancedAllTest, TestFalse2) 
{
	EXPECT_FALSE(CheckBalancedAll("(}{}][])"));
}

TEST(CheckBalancedAllTest, TestFalse3) 
{
	EXPECT_FALSE(CheckBalancedAll("[]({)"));
}
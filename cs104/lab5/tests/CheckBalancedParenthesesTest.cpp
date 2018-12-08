#include "gtest/gtest.h"
#include "../CheckBalanced.h"
#include <string>

TEST(CheckBalancedParenthesesTest, TestTrue1) 
{
	EXPECT_TRUE(CheckBalancedParentheses("()"));
}

TEST(CheckBalancedParenthesesTest, TestTrue2) 
{
	EXPECT_TRUE(CheckBalancedParentheses("(())"));
}

TEST(CheckBalancedParenthesesTest, TestTrue3) 
{
	EXPECT_TRUE(CheckBalancedParentheses("(()()()())"));
}

TEST(CheckBalancedParenthesesTest, TestTrue4) 
{
	EXPECT_TRUE(CheckBalancedParentheses("(((())))"));
}

TEST(CheckBalancedParenthesesTest, TestTrue5) 
{
	EXPECT_TRUE(CheckBalancedParentheses("(()((())()))"));
}

TEST(CheckBalancedParenthesesTest, TestFalse1) 
{
	EXPECT_FALSE(CheckBalancedParentheses("("));
}

TEST(CheckBalancedParenthesesTest, TestFalse2) 
{
	EXPECT_FALSE(CheckBalancedParentheses(")"));
}

TEST(CheckBalancedParenthesesTest, TestFalse3) 
{
	EXPECT_FALSE(CheckBalancedParentheses("((((((())"));
}

TEST(CheckBalancedParenthesesTest, TestFalse4) 
{
	EXPECT_FALSE(CheckBalancedParentheses("()))"));
}

TEST(CheckBalancedParenthesesTest, TestFalse5) 
{
	EXPECT_FALSE(CheckBalancedParentheses("(()()(()"));
}
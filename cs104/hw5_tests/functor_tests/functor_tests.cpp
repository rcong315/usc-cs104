//
// CS104 HW5 Functor test suite
//

#include <functor.h>

#include <gtest/gtest.h>

// set up fixtures
class FunctorFixture : public testing::Test
{
protected:
	NumStrComp numComp;
};

class FunctorSimple : public FunctorFixture {};
class FunctorTiebreaker : public FunctorFixture {};
class FunctorUnknownChars : public FunctorFixture {};

// ---------------------------------------------------------------------------------

TEST_F(FunctorSimple, Numbers)
{
	EXPECT_TRUE(numComp("0", "1"));
}

TEST_F(FunctorSimple, CapitalLetters)
{
	EXPECT_TRUE(numComp("A", "B"));
}

TEST_F(FunctorSimple, Word1)
{
	EXPECT_TRUE(numComp("t1000", "u1"));
}

TEST_F(FunctorSimple, Word2)
{
	EXPECT_TRUE(numComp("z0000", "azzz"));
}

TEST_F(FunctorSimple, RepeatedCharacter)
{
	EXPECT_TRUE(numComp("C", "CC"));
}

TEST_F(FunctorSimple, LongWord)
{
	//                                                v                                     v
	EXPECT_TRUE(numComp("supercalifragilisticexpialodocious", "supercalifragilisticexpialodoxious"));
}

TEST_F(FunctorSimple, ExactValue)
{
	// t should be worth 29, so it should be right between these two
	EXPECT_TRUE(numComp("T", "Aa91"));
	EXPECT_FALSE(numComp("T", "Aa9"));
}

// ---------------------------------------------------------------------------------

TEST_F(FunctorTiebreaker, SimpleLexicographic)
{
	// capital letters should get sorted first
	EXPECT_TRUE(numComp("A", "a"));
	EXPECT_TRUE(numComp("Bbbbbbbb", "bbbBBBbb"));
}

TEST_F(FunctorTiebreaker, ComplexLexicographic)
{
	// both words have value 97
	EXPECT_TRUE(numComp("Addenda1", "Zebra"));
}

TEST_F(FunctorTiebreaker, NotLexicographic)
{
	// will fail if lexicographic is always used
	EXPECT_FALSE(numComp("Addzz", "Zall"));
	EXPECT_TRUE(numComp("Zall", "Addzz"));
}

TEST_F(FunctorTiebreaker, Equal)
{
	EXPECT_FALSE(numComp("012", "012"));
	EXPECT_FALSE(numComp("zyzzyx!!!", "zyzzyx!!!"));
}

// ---------------------------------------------------------------------------------

TEST_F(FunctorUnknownChars, TreatedAsZero)
{
	EXPECT_TRUE(numComp("%^&%^*(A", "B"));
	EXPECT_TRUE(numComp("Item#3", "Item.4"));
}

TEST_F(FunctorUnknownChars, EmptyString)
{
	EXPECT_TRUE(numComp("", "#")); // lexical compare tiebreaker favors empty string
	EXPECT_FALSE(numComp("", ""));
	EXPECT_TRUE(numComp("", "1"));
	EXPECT_TRUE(numComp("", "0"));
}
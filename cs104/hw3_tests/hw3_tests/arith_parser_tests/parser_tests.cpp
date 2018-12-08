//
// Test cases for parser
//

#include "parser_utils.h"

#include <gtest/gtest.h>

TEST(Parser, JustNumber)
{
	std::string output;
	ASSERT_TRUE(runParser("JustNumber", "5", output));

	ASSERT_EQ("5", output);
}

TEST(ParserMalformed, OneOperandParen)
{
	std::string output;
	ASSERT_TRUE(runParser("OneOperandParen", "(91)", output));

	ASSERT_EQ("Malformed", output);
}

TEST(Parser, SpaceBefore)
{
	std::string output;
	ASSERT_TRUE(runParser("OneOperandParen", "     77", output));

	ASSERT_EQ("77", output);
}

TEST(Parser, SpaceAfter)
{
	std::string output;
	ASSERT_TRUE(runParser("OneOperandParen", "99  ", output));

	ASSERT_EQ("99", output);
}

TEST(Parser, SimpleLShift)
{
	std::string output;
	ASSERT_TRUE(runParser("SimpleLShift", "<10", output));

	ASSERT_EQ("20", output);
}

TEST(Parser, ShiftWithSpaces)
{
	std::string output;
	ASSERT_TRUE(runParser("SimpleLShift", "< <<10", output));

	ASSERT_EQ("80", output);
}


TEST(Parser, SimpleRShift)
{
	std::string output;
	ASSERT_TRUE(runParser("SimpleRShift", ">10", output));

	ASSERT_EQ("5", output);
}

TEST(Parser, SimpleAdd)
{
	std::string output;
	ASSERT_TRUE(runParser("SimpleAdd", "(4 + 2)", output));

	ASSERT_EQ("6", output);
}

TEST(Parser, AddWithoutSpaces)
{
	std::string output;
	ASSERT_TRUE(runParser("SimpleAdd", "(4+2)", output));

	ASSERT_EQ("6", output);
}

TEST(Parser, SimpleMultiply)
{
	std::string output;
	ASSERT_TRUE(runParser("SimpleMultiply", "(4 * 2)", output));

	ASSERT_EQ("8", output);
}

TEST(Parser, ThreeItemAdd)
{
	std::string output;
	ASSERT_TRUE(runParser("ThreeItemAdd", "(4 + 2 + 10)", output));

	ASSERT_EQ("16", output);
}

TEST(Parser, AddUnevenWhitespace)
{
	std::string output;
	ASSERT_TRUE(runParser("ThreeItemAdd", "(4 + 2+10)", output));

	ASSERT_EQ("16", output);
}


TEST(Parser, ThreeItemMultiply)
{
	std::string output;
	ASSERT_TRUE(runParser("ThreeItemMultiply", "(4 * 5 * 19)", output));

	ASSERT_EQ("380", output);
}

TEST(Parser, ShiftAdd)
{
	std::string output;
	ASSERT_TRUE(runParser("ShiftAdd", "(<<20 + 10)", output));

	ASSERT_EQ("90", output);
}

TEST(Parser, ShiftMultiply)
{
	std::string output;
	ASSERT_TRUE(runParser("ShiftMultiply", "(>>20 * 20)", output));

	ASSERT_EQ("100", output);
}

TEST(ParserMalformed, NestedParen)
{
	std::string output;
	ASSERT_TRUE(runParser("NestedParen", "(((22)))", output));

	ASSERT_EQ("Malformed", output);
}

TEST(ParserMalformed, EmptyParen)
{
	std::string output;
	ASSERT_TRUE(runParser("EmptyParen", "()", output));

	ASSERT_EQ("Malformed", output);
}

TEST(ParserMalformed, AddWithoutParens)
{
	std::string output;
	ASSERT_TRUE(runParser("MultiplyWithoutParens", "73 + 1", output));

	ASSERT_EQ("Malformed", output);
}

TEST(ParserMalformed, MultiplyWithoutParens)
{
	std::string output;
	ASSERT_TRUE(runParser("MultiplyWithoutParens", "4 * 2", output));

	ASSERT_EQ("Malformed", output);
}

TEST(Parser, NestedMultiply)
{
	std::string output;
	ASSERT_TRUE(runParser("NestedMultiply", "((10 * 15) * (4 * 2))", output));

	ASSERT_EQ("1200", output);
}

TEST(Parser, MultiplyShiftCombo)
{
	std::string output;
	ASSERT_TRUE(runParser("MultiplyShiftCombo", "<<(<<(16 + 10) + >>(20 + 1))", output));

	ASSERT_EQ("436", output);
}

TEST(Parser, SimpleMultiExprFile)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("SimpleMultiExprFile", (std::vector<std::string>{
		"10",
		"15",
	  	">15",
		"<15"}), output));

	ASSERT_EQ((std::vector<std::string>{"10", "15", "7", "30"}), output);
}

TEST(Parser, AdditionMultiExprFile)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("AdditionMultiExprFile", (std::vector<std::string>{
			"(5 + 3 + 5)",
			"(2 + 9 + 15 + 6 + 20)",
			"(<2 + <7 + >100 + >>100)",
			">>(100 + <1000 + 50 + >>10)"}), output));

	ASSERT_EQ((std::vector<std::string>{"13", "52", "93", "538"}), output);
}

TEST(Parser, MultiplicationMultiExprFile)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("MultiplicationMultiExprFile", (std::vector<std::string>{
			"(10 * 300 * 2)",
			"(<44 * <22 * <19)",
			"<(>>>>15 * 10 * 2)",
			"<>><(10 * 2 * >>101)"}), output));

	ASSERT_EQ((std::vector<std::string>{"6000", "147136", "0", "500"}), output);
}


TEST(Parser, ArbitraryWhitespace)
{
	std::string output;
	ASSERT_TRUE(runParser("ArbitraryWhitespace", "   << ( (  20 +  >> 10) * ( < > < 10 * 2)  )", output));

	ASSERT_EQ("3520", output);
}

TEST(Parser, BlankLines)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("BlankLines", (std::vector<std::string>{
			"( 15   + < < < < 10)",
			"",
			"",
			"(  19 +         >>><<<  << 29)"}), output));

	ASSERT_EQ((std::vector<std::string>{"175", "135"}), output);
}

TEST(ParserMalformed, DifferentOperators)
{
	std::string output;
	ASSERT_TRUE(runParser("DifferentOperators", "(10 + 4 * 3)", output));

	ASSERT_EQ("Malformed", output);
}

TEST(ParserMalformed, MissingPlusOperand)
{
	std::string output;
	ASSERT_TRUE(runParser("MissingPlusOperand", "(+ 10 + 20)", output));

	ASSERT_EQ("Malformed", output);
}

TEST(ParserMalformed, ShiftBeforePlus)
{
	std::string output;
	ASSERT_TRUE(runParser("ShiftBeforePlus", "(10 >> + 40)", output));

	ASSERT_EQ("Malformed", output);
}

TEST(ParserMalformed, InvalidOperator)
{
	std::string output;
	ASSERT_TRUE(runParser("InvalidOperator", "(10 ! 10)", output));

	ASSERT_EQ("Malformed", output);
}

TEST(ParserMalformed, PartiallyMalformedFile)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("PartiallyMalformedFile", (std::vector<std::string>{
			"(*40 * 40)",
			"((40 * 40) + (20 + 20))"}), output));

	ASSERT_EQ((std::vector<std::string>{"Malformed", "1640"}), output);
}

TEST(ParserStress, ExpressionAssortment)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("ExpressionAssortment", (std::vector<std::string>{
			"(10>> + 40)",
			"((20 + 33)",
			"(((5 * 9 * <<10)) + (10 * >> 422))",
			"",
	        "><<<  >(20 * (9      *10))   ",
	        "",
	        "((10 + 40) & (19 * 20))"}), output));

	ASSERT_EQ((std::vector<std::string>{"Malformed", "Malformed", "Malformed", "3600", "Malformed"}), output);
}

TEST(ParserStress, MegaExpressionAssortment)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("MegaExpressionAssortment", (std::vector<std::string>{
			"<<((8 + 19 + 100) * (>222 * 543 * <22))",
			"",
			"(5 * (10 + 2 + (200 * 2 * << 44 * (<>< >< >   10 * 29))))",
			"",
			"",
			"",
			"",
			"(((((((((((((((8 * 23 + 4)))))))))))))))",
			"",
			"(33 * 30 * 30 * 30 * 30 * 30 * 30 * 30      * (10 + 3 + 5 + 100)) >>"}), output));

	ASSERT_EQ((std::vector<std::string>{
		"1347222096",
		"102080060",
		"Malformed",
		"Malformed"}), output);
}

TEST(ParserStress, GrandFinale)
{
	std::vector<std::string> output;
	ASSERT_TRUE(runParser("GrandFinale", (std::vector<std::string>{
			"(  (   (10 + 20 + 30 + 40) * 209) + <<100)",
			"(40 >> << + 400 + 20 + 30)",
			"",
			"<<>(68 * 88 * <<>>20   ) + (100 + (200 + (>>>>300)))",
			"",
			"#malformed",
			"",
			"(( (10    + 300 +   59 + (39     * >> >>4 * 29994)) + 3400) * >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>50000)",
			"",
			"((500 + 50 - 400 ) * (49 + 5400))",
			"",
			"",
			"",
			"",
			"()",
			"",
			"((()))",
			"",
			"))()",
			"",
			"((20 * 20 * 20 * 20) + (20 * 20 * 20 * 20) + (20 * 20 * 20 * 20))"
	}), output));

	ASSERT_EQ((std::vector<std::string>{
			"21300",
			"Malformed",
			"Malformed",
			"Malformed",
			"0",
			"Malformed",
			"Malformed",
			"Malformed",
			"Malformed",
			"480000"
	}), output);
}
//
// CS104 HW6 graph search test suite
//

#include <gtest/gtest.h>

#include "coloring_checker.h"

TEST(Coloring, OneCountry)
{
	InputMap map = makeMap("AA");

	ASSERT_TRUE(testColoring("OneCountry", 1, map));
}

TEST(Coloring, SmallGivenMap)
{
	InputMap map = makeMap("FFFFFFFF\n"
	                       "FEEEDDDF\n"
	                       "FAABBCCF\n"
	                       "FFFFFFFF");

	ASSERT_TRUE(testColoring("SmallGivenMap", 6, map));
}

TEST(Coloring, MediumGivenMap)
{
	InputMap map = makeMap("AAAAAACCCCCCC\n"
	                       "AAAAAACCCCCCD\n"
	                       "BBBAAACCCCCDD\n"
	                       "BBAAAACCEEDDD\n"
	                       "BBBBBACDEEEDD\n"
	                       "BBBBBBDDDDDDD");

	ASSERT_TRUE(testColoring("MediumGivenMap", 5, map));
}

TEST(Coloring, LargeGivenMap)
{
	InputMap map = makeMap("FFFFFFFFFFFFFFF\n"
	                       "FFFFFFFFFFFFFFF\n"
	                       "FFEEEDDDDDDDDFF\n"
	                       "FFEEEDDDDDDDDFF\n"
	                       "FFEEEDDDDDDDDFF\n"
	                       "FFAABBBBBBCCCFF\n"
	                       "FFAABBBBBBCCCFF\n"
	                       "FFAABBBBBBCCCFF\n"
	                       "FFFFFFFFFFFFFFF\n"
	                       "FFFFFFFFFFFFFFF");

	ASSERT_TRUE(testColoring("LargeGivenMap", 6, map));
}

TEST(Coloring, Backtracking1)
{
	// note: this test produces a bunch of permutations of colors, so if you're timing out on this one, your code may have runtime issues when there are lots of valid combinations
	InputMap map = makeMap("HIJKGFG\n"
	                       "IIKKGGG\n"
	                       "KKKKLLE\n"
	                       "LLLLLDE\n"
	                       "MMMMMCN\n"
	                       "BBBBBCC\n"
	                       "BBBBACC");

	ASSERT_TRUE(testColoring("Backtracking1", 14, map, false));
}

TEST(Coloring, Backtracking2)
{
	InputMap map = makeMap("DDDDDDDDDDDDDDDD\n"
	                       "DDDCCCCCCCCCCCCD\n"
	                       "DDDCCCCCCCCCCCCD\n"
	                       "DDDBBBBBBBAAAAAA\n"
	                       "DDDDDDDDDDDDDDDA\n"
	                       "DDDEEEEEEEEEEEEA\n"
	                       "DDDEEEEEFFFFFFFA\n"
	                       "DDDFFFFFFFFFGHIA\n"
	                       "DDDDDDDDDDDDDDDD");

	ASSERT_TRUE(testColoring("Backtracking2", 9, map));
}

TEST(Coloring, WikipediaExample)
{
	InputMap map = makeMap("AAAAAAAAAAAAAAAAAAAA\n"
	                       "AAAAAAAAAAAAAAAAAAAA\n"
	                       "AAAAAAAAAAAAAAAAAAAA\n"
	                       "AABBBBBBBBEEEEEEEEAA\n"
	                       "AABBBBBBBBEEEEEEEEAA\n"
	                       "AABBFFIIIIIIIIHHEEAA\n"
	                       "AABBFFIIIIIIIIHHEEAA\n"
	                       "AABBFFJJJJJJJJHHEEAA\n"
	                       "AABBFFJJJJJJJJHHEEAA\n"
	                       "AACCFFGGGGGGGGHHDDAA\n"
	                       "AACCFFGGGGGGGGHHDDAA\n"
	                       "AACCCCCCCCDDDDDDDDAA\n"
	                       "AACCCCCCCCDDDDDDDDAA\n"
	                       "AAAAAAAAAAAAAAAAAAAA\n"
	                       "AAAAAAAAAAAAAAAAAAAA");

	ASSERT_TRUE(testColoring("WikipediaExample", 10, map));
}

TEST(Coloring, MaxLetters)
{
	InputMap map = makeMap("FLLEEEEEEEEEEEEEEEEEEEEEEEEEEE\n"
	                       "OOLEEEEHHHHHHHHHHHHHHHHHHHHHHE\n"
	                       "GBLIIJEHHHHHHHHHHHHHHHHHHHHHHE\n"
	                       "GBBAIJEHHHHHHHHHHHHHHHHHHHHHHE\n"
	                       "GGBAHJEHHHHHHHHHHHHHHHHHHHHHHE\n"
	                       "KGKKHJHHHHHHHHHHHHHHHHHHHHHHHE\n"
	                       "KKKHHJHHHHHHHHHHHHHHHHHHHHHHHE\n"
	                       "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHE\n"
	                       "HDDDDDDDDDDDDDDDDDDDDDDDDDDDDE\n"
	                       "HNNNNNNNNNNNNNNNNNNNNNNNNNNNNE\n"
	                       "HMMMMMMMMMMMMMMMMMMMMMMMMMMMME\n"
	                       "HCCCCCCCCCCCCCCCCCCCCCCCCCCCCE");

	ASSERT_TRUE(testColoring("MaxLetters", 15, map));
}

TEST(Coloring, MaxSize)
{
	InputMap map = makeMap("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
	                       "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
	                       "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
	                       "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
	                       "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
	                       "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA\n"
	                       "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA\n"
	                       "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA\n"
	                       "ABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBA\n"
	                       "ACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCA\n"
	                       "ACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCA\n"
	                       "ACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCA\n"
	                       "ACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCA\n"
	                       "ACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCA\n"
	                       "ADDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDCA\n"
	                       "AEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEECA\n"
	                       "AFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFA\n"
	                       "AGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHFFFFFFFFFA\n"
	                       "AGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHFFFFFFFFFA\n"
	                       "AGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHFFFFFFFFFA\n"
	                       "AGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHFFFFFFFFFA\n"
	                       "AGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHFFFFFFFFFA\n"
	                       "AHHHHHHHHHHHHHHHHHHHIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIHHHHHHHHHHHHHFFFFFHA\n"
	                       "MHHHHHHHHHHHHHHHHHHHIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIHHHHHFFFFFFFFFFHHHHA\n"
	                       "MHHHHHHHHHHHHHHHHHHHIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIHHHHHHHHHHHHHHHHHHHA\n"
	                       "MHHHHHHHHHHHHHHHHHHHIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIHHHHHHHHHHHHHHHHHHAA\n"
	                       "MIIIIIIIIIIIIIIIIIIIIIIIIIIIIIJJJJJJJJJJJJJJJJJJJJHHHHHHHHHHHHHHHHHHHHHHHHHHHHHA\n"
	                       "MIIIIIIIIIIIIIIIIIIIIIIIIIIIIIJJJJJJJJJJJJJJJJJJJJHHHHHHHHHHHHHHHHHHHHHHHHHHHHAA\n"
	                       "MIIIIIIIIIIIIIIIIIIIIIIIIIIIIIJJJJJJJJJJJJJJJJJJJJHHHHHHHHHHHHHHHHHHHHHHAAAAAAAA\n"
	                       "MIIIIIIIIIIIIIIIIIIIIIIIIIIIIIJJJJJJJJJJJJJJJJJJJJHHHHHHHHHHHHHHHHHHHHHHHHHHHHHO\n"
	                       "MJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJO\n"
	                       "MKKKKKKKKKKKKKKKKKKJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJJKKKKKKKKKKKKKKKKKKKKKKKKKKKO\n"
	                       "MKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKO\n"
	                       "MKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKKO\n"
	                       "MKKKKKKKKKKKKKKKKKKKLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLKKKKKKKKKKKKKKKKKKKKKKKKKKKKKO\n"
	                       "MLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLO\n"
	                       "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMLLLLLLLLLLLLLLMO\n"
	                       "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMO\n"
	                       "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMO\n"
	                       "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMO\n"
	                       "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMO\n"
	                       "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMO\n"
	                       "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "MMMMMMMMMMMMMMMMNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOONNNNNNNNNNNOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n"
	                       "OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");

	ASSERT_TRUE(testColoring("MaxSize", 15, map));
}
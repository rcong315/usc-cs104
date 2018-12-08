#include "gtest/gtest.h"
#include "../AllCombos.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool compareVectors(vector<string> first, vector<string> second){
	if(first.size() != second.size()) return false;

	sort(first.begin(), first.end());
	sort(second.begin(), second.end());

	for(size_t i = 0; i < first.size(); i++)
		if(first[i] != second[i]) return false;
	return true;
}

TEST(AllCombosTest, USC_2) 
{
	vector<string> result = {"UU", "US", "UC", "SU", "SS", "SC", "CU", "CS", "CC"};
	vector<string> temp;
	AllCombos(temp, "USC", 2);
	EXPECT_TRUE(compareVectors(temp, result));
}

TEST(AllCombosTest, CS104_2) {
	vector<string> result = {"CC", "CS", "C1", "C0", "C4", "SC", "SS", "S1", "S0", "S4", "1C", "1S", "11", "10", "14", "0C", "0S", "01", "00", "04", "4C", "4S", "41", "40", "44"};
	vector<string> temp;
	AllCombos(temp, "CS104", 2);
	EXPECT_TRUE(compareVectors(temp, result));
}

TEST(AllCombosTest, COTE_3) 
{
	vector<string> result = {"CCC", "CCO", "CCT", "CCE", "COC", "COO", "COT", "COE", "CTC", "CTO", "CTT", "CTE", "CEC", "CEO", "CET", "CEE", "OCC", "OCO", "OCT", "OCE", "OOC", "OOO", "OOT", "OOE", "OTC", "OTO", "OTT", "OTE", "OEC", "OEO", "OET", "OEE", "TCC", "TCO", "TCT", "TCE", "TOC", "TOO", "TOT", "TOE", "TTC", "TTO", "TTT", "TTE", "TEC", "TEO", "TET", "TEE", "ECC", "ECO", "ECT", "ECE", "EOC", "EOO", "EOT", "EOE", "ETC", "ETO", "ETT", "ETE", "EEC", "EEO", "EET", "EEE"};
	vector<string> temp;
	AllCombos(temp, "COTE", 3);
	EXPECT_TRUE(compareVectors(temp, result));
}

// for(size_t i = 0; i < temp.size(); i++) {
// 	cout << "\"" << temp[i] << "\", ";
// }

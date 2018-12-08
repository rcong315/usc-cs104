#include "gtest/gtest.h"
#include "../traversal.h"

#include <vector>
#include <iostream>

using namespace std;

TEST(PreOrderTest, PreOrderTest) {
	//Leaf Nodes
	Node n4(nullptr, nullptr, 4);
	Node n7(nullptr, nullptr, 7);
	Node n1(nullptr, nullptr, 1);
	Node n13(nullptr, nullptr, 13);

	Node n6(&n4, &n7, 6);
	Node n3(&n1, &n6, 3);

	Node n14(&n13, nullptr, 14);
	Node n10(nullptr, &n14, 10);

	Node n8(&n3, &n10, 8);

	vector<int> result;
	vector<int> cmp = {8, 3, 1, 6, 4, 7, 10, 14, 13};

	PreOrder(result, &n8);

	ASSERT_EQ(cmp.size(), result.size());
	for(int i = 0; i < (int)result.size(); i++) {
		ASSERT_EQ(cmp[i], result[i]);
	}
}
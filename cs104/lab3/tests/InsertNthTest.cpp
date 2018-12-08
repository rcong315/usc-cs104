#include "gtest/gtest.h"
#include "../LinkedList.h"
#include <vector>

void compare(LinkedList& ll, std::vector<int> cmp) {
	int i;
	Node* head;
	for(head = ll.head, i = 0; head != nullptr && i < (int)cmp.size(); head = head->next, i++) {
		EXPECT_EQ(cmp[i], head->data);
	}
}

TEST(InsertNthTest, TestInsertInBounds) 
{
	LinkedList ll;
	ll.add(2);
	ll.add(0);
	ll.InsertNth(1, 1);
	std::vector<int> cmp = {0, 1, 2};
	compare(ll, cmp);
}

TEST(InsertNthTest, TestInsert0Empty) {
	LinkedList ll;
	ll.InsertNth(0, 0);
	std::vector<int> cmp = {0};
	compare(ll, cmp);
}

TEST(InsertNthTest, TestInsert0NotEmpty) {
	LinkedList ll;
	ll.add(1);
	ll.InsertNth(0, 0);
	std::vector<int> cmp = {0, 1};
	compare(ll, cmp);
}

TEST(InsertNthTest, TestInsertEnd) {
	LinkedList ll;
	ll.add(1);
	ll.add(0);
	ll.InsertNth(2, 2);
	std::vector<int> cmp = {0, 1, 2};
	compare(ll, cmp);
}

TEST(InsertNthTest, TestInsertOutOfBoundsTooHigh) {
	LinkedList ll;
	ll.add(1);
	ll.add(0);
	ll.InsertNth(3, 3);
	ll.InsertNth(10, 10);
	std::vector<int> cmp = {0, 1};
	compare(ll, cmp);
}

TEST(InsertNthTest, TestInsertOutOfBoundsNegative) {
	LinkedList ll;
	ll.add(1);
	ll.add(0);
	ll.InsertNth(-1, -1);
	std::vector<int> cmp = {0, 1};
	compare(ll, cmp);
}
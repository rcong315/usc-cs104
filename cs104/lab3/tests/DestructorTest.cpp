#include "gtest/gtest.h"
#include "../LinkedList.h"
#include <stdio.h>
#include <vector>

void compare(LinkedList& ll, std::vector<int>& cmp) {
	int i;
	Node* head;
	for(head = ll.head, i = 0; head != nullptr && i < (int)cmp.size(); head = head->next, i++) {
		EXPECT_EQ(cmp[i], head->data);
	}
}

TEST(DestructorTest, TestAdd) 
{
	LinkedList ll;
	ll.add(1);
	ll.add(0);
	std::vector<int> cmp = {0, 1};
	compare(ll, cmp);
}
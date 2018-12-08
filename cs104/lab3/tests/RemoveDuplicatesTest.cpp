#include "gtest/gtest.h"
#include "../LinkedList.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>

void compare(LinkedList& ll, std::vector<int>& cmp) {
	int i;
	Node* head;
	for(head = ll.head, i = 0; head != nullptr && i < (int)cmp.size(); head = head->next, i++) {
		EXPECT_EQ(cmp[i], head->data);
	}
}

TEST(RemoveDuplicatesTest, EveryNodeHasOneDuplicate) 
{
	LinkedList ll;
	ll.add(1);
	ll.add(1);
	ll.add(0);
	ll.add(0);
	ll.RemoveDuplicates();
	std::vector<int> cmp = {0, 1};
	compare(ll, cmp);
}

TEST(RemoveDuplicatesTest, NoDuplicates) {
	LinkedList ll;
	ll.add(1);
	ll.add(0);
	ll.RemoveDuplicates();
	std::vector<int> cmp = {0, 1};
	compare(ll, cmp);
}

TEST(RemoveDuplicatesTest, AllSameNumber) {
	LinkedList ll;
	ll.add(0);
	ll.add(0);
	ll.add(0);
	ll.add(0);
	ll.add(0);
	ll.RemoveDuplicates();
	std::vector<int> cmp = {0};
	compare(ll, cmp);
}

TEST(RemoveDuplicatesTest, Empty){
	LinkedList ll;
	ll.RemoveDuplicates();
	EXPECT_EQ(nullptr, ll.head);
}

TEST(RemoveDuplicatesTest, SomeMayHaveDupes) {
	LinkedList ll;
	int size = 4;
	std::vector<int> cmp;
	std::vector<int>::iterator it;

	for(int i = size - 1; i >= 0; i--) {
		int dupes = rand() % 10 + 1;
		for(int j = 0; j < dupes; j++) {
			ll.add(i);
		}
		it = cmp.begin();
		cmp.insert(it, i);
	}

	ll.RemoveDuplicates();

	compare(ll, cmp);
}
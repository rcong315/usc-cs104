#include "selection_sort.h"

Item* findMin(Item* head) {
	//if list is empty
	if (head == nullptr) {
 		return nullptr;
	}

	//set min to first item
	Item* minItem = head;
	int min = head -> getValue();
	Item* temp = head -> next;
	
	//loop through list
	while (temp != nullptr) {
		//check if item's value is less than min
		if (temp -> getValue() < min) {
			//set new min
			minItem = temp;
			min = temp -> getValue();
		}
		temp = temp -> next;
	}
	//return min
	return minItem;
}

Item* LLSelectionSort(Item* head) {
	//if list is empty
	if (head == nullptr) {
		return nullptr;
	}

	//if head is the only item return head
	if (head -> next == nullptr) {
		return head;
	}
	
	//find min in list and set as new head
	Item* newHead = findMin(head);
	//if min is at head move head over one
	if (newHead == head) {
		head = head -> next;
		head -> prev = nullptr;
	}

	//check if new head is not at end
	else if (newHead -> next != nullptr) {
		newHead -> prev -> next = newHead -> next;
		newHead -> next -> prev = newHead -> prev;
	}

	//if new head is at end
	else {
		newHead -> prev -> next = nullptr;
	}
	
	//disconnect new head from list 
	newHead -> prev = nullptr;
	newHead -> next = nullptr;
	//create new tail and a temporary item 
	Item* newTail = newHead;
	Item* temp = newHead;

	//loop through list
	while (temp != nullptr) {
		//check if there is only one item left
		if (head -> next == nullptr) {
			//set new tail to head
			newTail = head;
			temp -> next = newTail;
			newTail -> prev = temp;
			return newHead;
		}

		//set new tail as the next min
		newTail = findMin(head);
		//if new tail is at the head move head over one 
		if (newTail == head) {
			head = head -> next;
			head -> prev = nullptr;
		}

		//check if new tail is not at end of list
		else if (newTail -> next != nullptr) {
			newTail -> prev -> next = newTail -> next;
			newTail -> next -> prev = newTail -> prev;
		}

		//if new tail is at the end
		else{
			newTail -> prev -> next = nullptr;
		}

		//add new tail to list
		newTail -> prev = temp;
		newTail -> next = nullptr;
		temp -> next = newTail;
		temp = temp -> next;
	} 
	//return new head
	return newHead;
}


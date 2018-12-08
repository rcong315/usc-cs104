#include "circular_list_int.h"

CircularListInt::CircularListInt() {
	
}

CircularListInt::~CircularListInt() {
	//while the list is not empty keep on removing the head
	while (!empty()) {
		remove(0);
	}
}

CircularListInt::Item* CircularListInt::findItem(size_t index) const {
	//if list is empty
	if (empty()) {
		return nullptr;
	}

	//reduce index to avoid looping through the list multiple times
	size_t loc = index % count;
	Item* found = head;
	//loop to the desired item
	if (loc == count - 1) {
		return found -> prev;
	}
	for (size_t i = 0; i < loc; i++) {
		found = found -> next;
	}
	//return item
	return found;
}

int CircularListInt::get(size_t index) const{
	//if list is empty
	if (empty()) {
		return 0;
	}
	//find the item and get its value
	return findItem(index) -> value;
}

size_t CircularListInt::size() const{
	//return the size;
	return count;
}

bool CircularListInt::empty() const{
	//return whether count is 0
	return count == 0;
}

void CircularListInt::push_back(int value) {
	Item* newTail = new Item(value);
	//if list is empty
	if (empty()) {
		//set head to the item and increase list size
		head = newTail;
		head -> next = head;
		head -> prev = head;
		count++;
		return;
	}

	Item* tail = head -> prev;
	//add the new items
	newTail -> next = head;
	newTail -> prev = tail;
	head -> prev = newTail;
	tail -> next = newTail;
	//increase list size
	count++;
}

void CircularListInt::set(size_t index, int value) {
	//if list is empty
	if (empty()) {
		return;
	}

	//reduce index to avoid looping through list multiple times
	size_t loc = index % count;
	Item* item = head;
	//loop to desired item
	for (size_t i = 0; i < loc; i++) {
		item = item -> next;
	}
	//set the items value to value
	item -> value = value;
}

void CircularListInt::remove(size_t index) {
	//if list is empty
	if (empty()) {
		return;
	}

	//reduce index
	size_t loc = index % count;
	//set item to point to head
	Item* temp = head;

	//if list is only 1 element
	if (size() == 1) {
		temp -> next = nullptr;
		temp -> prev = nullptr;
		head = nullptr;
		delete temp;
		count--;
		return;
	}
	
	//if the location is at the head
	if (loc == 0) {
		//decrease the size of the list
		count--;
		
		head = temp -> next;
		//if the new size is one
		if (size() == 1) {
			//delete temporary item and set last item to point to itself
			temp -> next = nullptr;
			temp -> prev = nullptr;
			temp = nullptr;
			head -> next = head;
			head -> prev = head;
			delete temp;
			return;
		}

		//otherwise remove the head and move the head to the next item
		head -> prev = temp -> prev;
		temp -> prev -> next = head;
		temp -> next = nullptr;
		temp -> prev = nullptr;
		temp = nullptr;
		delete temp;
		return;
	}

	//if item is at the end
	else if (loc == count - 1) {
		count--;
		temp = temp -> prev;
		head -> prev = temp -> prev;
		head -> prev -> next = head;
		temp -> next = nullptr;
		temp -> prev = nullptr;
		temp = nullptr;
		delete temp;
		return;
	}

	//if item is not the head loop to it
	for (size_t i = 0; i < loc; i++) {
		temp = temp -> next;
	}

	//remove the item
	temp -> prev -> next = temp -> next;
	temp -> next -> prev = temp -> prev;
	delete temp;
	//decrease list size
	count--;
}

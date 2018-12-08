#include "inventory.h"
#include <iostream>

Inventory::Inventory() {
	
}

void Inventory::addItem(std::string item, int amt) {
	vector<Item>::iterator it;
	for (it = begin(); it != end(); ++it) {
		if (it -> name == item) {
			it -> amount += amt;
			return;
		}
	}
	Item newItem(item, amt);
	push_back(newItem);
}

void Inventory::removeItem(std::string item) {
	vector<Item>::iterator it;
	for (it = begin(); it != end(); ++it) {
		if (it -> name == item) {
			erase(it);
			return;
		}
	}
}

int Inventory::getNumItems(std::string item) {
	int total = 0;
	vector<Item>::iterator it;
	for (it = begin(); it != end(); ++it) {
		if (it -> name == item) {
			total += it -> amount;
		}
	}
	return total;
}

void Inventory::printAllItems() {
	vector<Item>::iterator it;
	for (it = begin(); it != end(); ++it) {
		std::cout << it -> name << " " << it -> amount << std::endl;
	}
}
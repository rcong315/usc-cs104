#include "order.h"
#include <iostream>

Order::Item::Item(const std::string& n, int c)
: name(n)
, count(c)
{
}

// Constructor
Order::Order()
{
}

// Constructor which allocates one item
Order::Order(const std::string& name)
{
	mItems.push_back(new Item(name, 1));
}

// Copy Constructor - Part 3
Order::Order(const Order &rhs)
{
	for( size_t i = 0; i < rhs.mItems.size(); ++i ){
		mItems.push_back(new Item(*rhs.mItems[i]));
	}
}

Order::~Order()
{
	clearOrder();
}

// Prints all items and their amounts.
void Order::displayOrder() const
{
	std::cout << "The current order is: " << std::endl;

	// Check if empty
	if(mItems.empty())
	{
		std::cout << "Empty" << std::endl;
		return;
	}

	// Display each item and its amount
	for (size_t i = 0; i < mItems.size(); ++i)
	{
		std::cout << mItems[i]->name << " " << mItems[i]->count << std::endl;
	}
}

// Deletes all items in variable ITEMS. - Part 2
void Order::clearOrder()
{
	for( size_t i = 0; i < mItems.size(); i++){
		delete mItems[i];
	}
	mItems.clear();
}

// Assigns Order RHS values to the current Order's values - Part 4
Order& Order::operator=(const Order &rhs)
{
	// Starter code: self-assignment can cause unseen problems. It won't
		// happen in this program, but let's get you in the habit early.
	if(this == &rhs)
		return *this;

	// TODO
	this->clearOrder();
	
	for( size_t i = 0; i < rhs.mItems.size(); ++i ){
		this->mItems.push_back(new Item(*rhs.mItems[i]));
	}

	return *this;
}

/* 
Part 4
This operator should create a new Order that represents the
combined outcome of the current Order and the Order passed in via
parameter.
Note: It should not directly modify the current Order, but return
a copy of the combined Order instead. 
*/
Order Order::operator+(const Order &rhs) const
{
	// Starter code: operator+ should not modify THIS, so we make a copy
	Order result(*this);

	// TODO

	int burgers = 0, fries = 0, drinks = 0, vegetables = 0;
	bool yesB = false, yesF = false, yesD = false, yesV = false;

	for( size_t i = 0; i < rhs.mItems.size(); ++i){
		if( rhs.mItems[i]->name == "Burger" ){
			burgers += rhs.mItems[i]->count;
		}
		else if( rhs.mItems[i]->name == "Fries" ){
			fries += rhs.mItems[i]->count;
		}
		else if( rhs.mItems[i]->name == "Drink" ){
			drinks += rhs.mItems[i]->count;
		}
		else if( rhs.mItems[i]->name == "Vegetables" ){
			vegetables += rhs.mItems[i]->count;
		}
	}

	for( size_t i = 0; i < result.mItems.size(); ++i){
		if( result.mItems[i]->name == "Burger" ){
			result.mItems[i]->count += burgers;
			yesB = true;
		}
		else if( result.mItems[i]->name == "Fries" ){
			result.mItems[i]->count += fries;
			yesF = true;
		}
		else if( result.mItems[i]->name == "Drink" ){
			result.mItems[i]->count += drinks;
			yesD = true;
		}
		else if( result.mItems[i]->name == "Vegetables" ){
			result.mItems[i]->count += vegetables;
			yesV = true;
		}
	}

	if( burgers != 0 && !yesB ){
		result.mItems.push_back(new Item("Burger", burgers));
	}
	if( fries != 0 && !yesF ){
		result.mItems.push_back(new Item("Fries", fries));
	}
	if( drinks != 0 && !yesD ){
		result.mItems.push_back(new Item("Drink", drinks));
	}
	if( vegetables != 0 && !yesV ){
		result.mItems.push_back(new Item("Vegetables", vegetables));
	}


	return result;
}
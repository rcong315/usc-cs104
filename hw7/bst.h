#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<Key, Value>& getItem() const;
	std::pair<Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Key& getKey();
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);

protected:
	std::pair<Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the deleteAll() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<Key, Value>& Node<Key, Value>::getItem() const
{
	return mItem;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& Node<Key, Value>::getItem()
{
	return mItem;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
	return mItem.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
	return mItem.second;
}

/**
* A non-const getter for the key.
*/
template<typename Key, typename Value>
Key& Node<Key, Value>::getKey()
{
	return mItem.first;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
	return mParent;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
	return mLeft;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
	return mRight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
	mParent = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
	mLeft = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
	mRight = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
	mItem.second = value;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
  		virtual void insert(const std::pair<Key, Value>& keyValuePair); //TODO
        virtual void remove(const Key& key); //TODO
  		void clear(); //TODO
  		void print() const;
  		bool isBalanced() const; //TODO

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<Key,Value>& operator*() const;
				std::pair<Key,Value>* operator->() const;

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;

				friend class BinarySearchTree<Key, Value>;
		};

	public:
		iterator begin() const;
		iterator end() const;
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;

	public:
		void print() {this->printRoot(this->mRoot);}

	private:
		Node<Key, Value>* findPredecessor(Node<Key, Value>* node);
		void recursiveClear(Node<Key, Value>* node);
		bool isBalancedHelper(Node<Key, Value>* node) const;
		int height(Node<Key, Value>* node) const;
		virtual Node<Key, Value>* createNode(const std::pair<Key, Value>& keyValuePair);

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const
{
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const
{
	return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree()
{
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	//create node to insert
	Node<Key, Value>* toInsert = createNode(keyValuePair);

	//insert as root if there is no root
	if (mRoot == NULL) {
		mRoot = toInsert;
		return;
	}

	//create new node pointer to go through tree
	Node<Key, Value>* temp = mRoot;
	//loop through tree
	while (temp != NULL) {

		//replace value if key is already in the tree
		if (keyValuePair.first == temp -> getKey()) {
			temp -> setValue(keyValuePair.second);
			delete toInsert;
			return;
		}

		//go left if the key is less and insert if there is no left child
		else if (keyValuePair.first < temp -> getKey()) {
			if (temp -> getLeft() != NULL) {
				temp = temp -> getLeft();
			}
			else {
				temp -> setLeft(toInsert);
				toInsert -> setParent(temp);
				return;
			}
		}

		//go right if the key is more and insert if there is no right child
		else {
			if (temp -> getRight() != NULL) {
				temp = temp -> getRight();
			}
			else {
				temp -> setRight(toInsert);
				toInsert -> setParent(temp);
				return;
			}
		}
	}
}

/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	//find the node we want to delete
	Node<Key, Value>* toDelete = internalFind(key);
	//return if the node is not in the tree
	if (toDelete == NULL) {
		delete toDelete;
		return;
	}

	//create pointers to the node's neighbors
	Node<Key, Value>* parent = toDelete -> getParent();
	Node<Key, Value>* left = toDelete -> getLeft();
	Node<Key, Value>* right = toDelete -> getRight();

	//if we are deleting the root
	if (toDelete == mRoot) {

		//no children nodes, simple delete
		if (left == NULL && right == NULL) {
			delete toDelete;
			mRoot = NULL;
			return;
		}

		//has a left child, promote the left child
		if (right == NULL) {
			left -> setParent(NULL);
			mRoot = left;
		}

		//has right child, promote the right child
		else if (left == NULL) {
			right -> setParent(NULL);
			mRoot = right;
		}

		//has two children, promote the predecessor
		else {
			Node<Key, Value>* predecessor = findPredecessor(toDelete);
			if (predecessor == predecessor -> getParent() -> getLeft()) {
				predecessor -> getParent() -> setLeft(predecessor -> getLeft());
			}
			else {
				predecessor -> getParent() -> setRight(predecessor -> getLeft());
			}
			if (predecessor == left) {
				left = predecessor -> getLeft();
			}
			predecessor -> setParent(NULL);
			predecessor -> setLeft(left);
			predecessor -> setRight(right);
			if(left != NULL) {
				predecessor -> getLeft() -> setParent(predecessor);
			}
			if(right != NULL) {
				predecessor -> getRight() -> setParent(predecessor);
			}
			mRoot = predecessor;
		}
	}

	//not deleting root node
	else {

		//no children nodes
		if (left == NULL && right == NULL) {
			if (toDelete == parent -> getLeft()) {
				parent -> setLeft(NULL);
			}
			else if (toDelete == parent -> getRight()) {
				parent -> setRight(NULL);
			}
		}

		//has a left child, promote the left child
		else if (right == NULL) {
			if (toDelete == parent -> getLeft()) {
				parent -> setLeft(left);
			}
			else if (toDelete == parent -> getRight()) {
				parent -> setRight(left);
			}
			left -> setParent(parent);
		}

		//has a right child, promote the right child
		else if (left == NULL) {
			if (toDelete == parent -> getLeft()) {
				parent -> setLeft(right);
			}
			else if (toDelete == parent -> getRight()) {
				parent -> setRight(right);	
			}
			right -> setParent(parent);
		}

		//has two children, promote the predecessor
		else {
			Node<Key, Value>* predecessor = findPredecessor(toDelete);
			if (predecessor == predecessor -> getParent() -> getLeft()) {
				predecessor -> getParent() -> setLeft(predecessor -> getLeft());
			}
			else {
				predecessor -> getParent() -> setRight(predecessor -> getLeft());
			}
			if (predecessor == left) {
				left = predecessor -> getLeft();
			}
			if (toDelete == parent -> getLeft()) {
				parent -> setLeft(predecessor);
			}
			else if (toDelete == parent -> getRight()) {
				parent -> setRight(predecessor);
			}
			predecessor -> setParent(parent);
			predecessor -> setLeft(left);
			predecessor -> setRight(right);
			if(left != NULL) {
				predecessor -> getLeft() -> setParent(predecessor);
			}
			if(right != NULL) {
				predecessor -> getRight() -> setParent(predecessor);
			}
		}
	}

	//delete the node
	delete toDelete;
}

/**
* A method to remove all contents of the tree and reset the values in the tree
* for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	//call helper
	recursiveClear(mRoot);

	//set root as null
	mRoot = NULL;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	//return null if tree is empty
	if (mRoot == NULL) {
		return NULL;
	}

	//keep on going left
	Node<Key, Value>* temp = mRoot;
	while (temp -> getLeft() != NULL) {
		temp = temp -> getLeft();
	}

	//return leftmost node
	return temp;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	//return null if the tree is empty
	if (mRoot == NULL) {
		return NULL;
	}

	//loop through tree
	Node<Key, Value>* temp = mRoot;
	while (temp != NULL) {

		//return if found
		if (key == temp -> getKey()) {
			return temp;
		}

		//go left if less
		else if (key < temp -> getKey()) {
			temp = temp -> getLeft();
		}

		//go right if more
		else {
			temp = temp -> getRight();
		}
	}

	//not found
	return NULL;
}

/**
 * Return true iff the BST is an AVL Tree.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	//call helper
  	return isBalancedHelper(mRoot);
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findPredecessor(Node<Key, Value>* node) 
{
	//find the node we want to find the predecessor of
	Node<Key, Value>* predecessor = internalFind(node -> getKey());

	//go left once
	if (predecessor -> getLeft() != NULL) {
		predecessor = predecessor -> getLeft();
	}

	//if there is no left, there is no predecessor
	else {
		return NULL;
	}

	//keep on going right
	while (predecessor -> getRight() != NULL) {
		predecessor = predecessor -> getRight();
	}

	//return the predecessor
	return predecessor;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::recursiveClear(Node<Key, Value>* node) 
{
	//stop when node is null	
	if (node == NULL) {
		return;
	}

	//recursive call to left and right child
	if (node -> getLeft() != NULL) {
		recursiveClear(node -> getLeft());
	}
	if (node -> getRight() != NULL) {
		recursiveClear(node -> getRight());
	}

	//delete each node
	delete node;
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedHelper(Node<Key, Value>* node) const
{
	//if node is null then it is balanced
	if (node == NULL) {
		return true;
	}

	//find height of left and right
	int lheight = height(node -> getLeft()); 
	int rheight = height(node -> getRight()); 
	int dif = lheight - rheight;

	//if the difference is less than 1 return true, otherwise return false
	if(dif >= -1 && dif <= 1 && isBalancedHelper(node -> getLeft()) && isBalancedHelper(node -> getRight())) {
    	return true; 
	}
	return false; 
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(Node<Key, Value>* node) const
{ 
	//height is 0 if null
	if(node == NULL) {
    	return 0; 
	}

	//recursive call to left and right child
	int lheight = height(node -> getLeft());
	int rheight = height(node -> getRight());
	
	//return higher height + 1
	if (lheight > rheight) {
		return 1 + lheight;
	}
	return 1 + rheight;
} 

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::createNode(const std::pair<Key, Value>& keyValuePair) 
{
	//return pointer to node
	return new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
}

/**
 * Lastly, we are providing you with a print function, BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->mRoot)

   It will print up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif

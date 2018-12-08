#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "rotateBST.h"
#include <algorithm>

using namespace std;

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();
    
    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);
    
    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;
    
protected:
    int mHeight;
};

/*
 --------------------------------------------
 Begin implementations for the AVLNode class.
 --------------------------------------------
 */

/**
 * Constructor for an AVLNode. Nodes are initialized with a height of 0.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
: Node<Key, Value>(key, value, parent)
, mHeight(0)
{
    
}

/**
 * Destructor.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{
    
}

/**
 * Getter function for the height.
 */
template<typename Key, typename Value>
int AVLNode<Key, Value>::getHeight() const
{
    return mHeight;
}

/**
 * Setter function for the height.
 */
template<typename Key, typename Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    mHeight = height;
}

/**
 * Getter function for the parent. Used since the node inherits from a base node.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->mParent);
}

/**
 * Getter function for the left child. Used since the node inherits from a base node.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->mLeft);
}

/**
 * Getter function for the right child. Used since the node inherits from a base node.
 */
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->mRight);
}

/*
 ------------------------------------------
 End implementations for the AVLNode class.
 ------------------------------------------
 */

/**
 * A templated balanced binary search tree implemented as an AVL tree.
 */
template <class Key, class Value>
class AVLTree : public rotateBST<Key, Value>
{
public:
    // Methods for inserting/removing elements from the tree. You must implement
    // both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void remove(const Key& key) override;
    
private:
    Node<Key, Value>* createNode(const std::pair<Key, Value>& keyValuePair) {
        return new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
    }
    
protected:
    
    
private:
    /* Helper functions are strongly encouraged to help separate the problem
     into smaller pieces. You should not need additional data members. */
    void updateHeight(AVLNode<Key, Value>* node);
    int height(AVLNode<Key, Value>* node) const;
    int balancedHelper(AVLNode<Key, Value>* node) const;
    void leftRotate(AVLNode<Key, Value>* r);
    void rightRotate(AVLNode<Key, Value>* r);
    
};

/*
 --------------------------------------------
 Begin implementations for the AVLTree class.
 --------------------------------------------
 */


/**
 * Insert function for a key value pair. Finds location to insert the node and then balances the tree.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    //call bst insert
    BinarySearchTree<Key, Value>::insert(keyValuePair);
    
    //create pointer to inserted node and change to avl node pointer
    Node<Key, Value>* n = BinarySearchTree < Key, Value> ::internalFind(keyValuePair.first);
    AVLNode<Key, Value>* node = static_cast<AVLNode<Key, Value>*>(n);
    //update height of node
    updateHeight(node);

    //loop through the tree
    node = node->getParent();
    while (node != NULL) {
        //update height and check for balance
        //if unbalanced perform necessary rotations
        updateHeight(node);
        int balance = balancedHelper(node);
        if (balance > 1 && keyValuePair.first < node -> getLeft() -> getKey()) {
            rightRotate(node);
            node = node -> getParent();
        }
        else if (balance < -1 && keyValuePair.first > node -> getRight() -> getKey()) {
            leftRotate(node);
            node = node -> getParent();
        }
        else if (balance > 1 && keyValuePair.first > node -> getLeft() -> getKey()) {
            leftRotate(node -> getLeft());
            rightRotate(node);
            node = node -> getParent();
        }
        else if (balance < -1 && keyValuePair.first < node -> getRight() -> getKey()) {
            rightRotate(node -> getRight());
            leftRotate(node);
            node = node -> getParent();
        }
        //change node to its parent
        node = node -> getParent();
    }
}

/**
 * Remove function for a given key. Finds the node, reattaches pointers, and then balances when finished.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::remove(const Key& key)
{
    //cast node to avl node
    AVLNode<Key, Value>* node = dynamic_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
    //do nothing if the node is not in the tree
    if(node == NULL) {
        return;
    }

    //find out wich side of its parent node is on
    AVLNode<Key, Value>* parent = node -> getParent();
    bool isLeft = false;
    if (parent != NULL){
        isLeft = parent -> getLeft() == node;
    }

    //call bst remove
    BinarySearchTree<Key, Value>::remove(key);

    //change node if it has a parent
    if (parent){
        if (isLeft) {
            node = parent -> getLeft();
        }
        else {
            node = parent -> getRight();
        }
        if (node == 0){
            node = parent;
        }
    }
    //otherwise node is the root
    else{
        node = static_cast<AVLNode<Key, Value>*>(this -> mRoot);
    }

    //update heights
    if (node){
        updateHeight(node -> getLeft());
        updateHeight(node -> getRight());
    }

    //loop through tree
    while (node != NULL) {
        //update heights and check balance
        //if unbalanced do rotations
        updateHeight(node);
        int balance = balancedHelper(node);
        int lbalance = balancedHelper(node -> getLeft());
        int rbalance = balancedHelper(node -> getRight());
        if (balance > 1 && lbalance >= 0){
            rightRotate(node);
            node = node -> getParent();
        }
        else if (balance < -1 && rbalance <= 0){
            leftRotate(node);
            node = node -> getParent();
        }
        else if (balance > 1 && lbalance < 0) {
            leftRotate(node -> getLeft());
            rightRotate(node);
            node = node -> getParent();
        }
        else if (balance < -1 && rbalance > 0) {
            rightRotate(node -> getRight());
            leftRotate(node);
            node = node -> getParent();
        }
        //change node to its parent
        node = node -> getParent();
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::updateHeight(AVLNode<Key, Value>* node)
{
    //set node's height to 1 more than it's children's height (the greater one)
    if (node != NULL) {
        int h = max(height(node -> getLeft()), height(node -> getRight()));
        node -> setHeight(h + 1);
    }
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::height(AVLNode<Key, Value>* node) const
{
    //return 0 if the node is null, otherwise return its height
    if (node == NULL) {
        return 0;
    }
    return node -> getHeight();
}

template<typename Key, typename Value>
int AVLTree<Key, Value>::balancedHelper(AVLNode<Key, Value>* node) const
{
    //return the difference in heights of left and right subtrees
    if (node == NULL) {
        return 0;
    }
    return height(node -> getLeft()) - height(node -> getRight());
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::leftRotate(AVLNode<Key, Value>* r) 
{
    //rotate and update heights
    rotateBST<Key, Value>::leftRotate(r);
    updateHeight(r);
    updateHeight(r -> getParent());
}

template <typename Key, typename Value>
void AVLTree<Key, Value>::rightRotate(AVLNode<Key, Value>* r) 
{
    //rotate and update heights
    rotateBST<Key, Value>::rightRotate(r);
    updateHeight(r);
    updateHeight(r -> getParent());
}

/*
 ------------------------------------------
 End implementations for the AVLTree class.
 ------------------------------------------
 */

#endif

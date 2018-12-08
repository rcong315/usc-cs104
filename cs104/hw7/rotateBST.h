#ifndef ROTATEBST_H
#define ROTATEBST_H
 
#include <unordered_set>
#include "bst.h"
 
template <typename Key, typename Value>
class rotateBST: public BinarySearchTree<Key, Value>
{
public:
    bool sameKeys(const rotateBST& t2) const;
    void transform(rotateBST& t2) const;
     
protected:
    void leftRotate(Node<Key, Value>* r);
    void rightRotate(Node<Key, Value>* r);
     
private:
    void getKeys(std::unordered_set<Key>& keys, Node<Key, Value>* r) const;
    void transformHelperRight(rotateBST& t2, Node<Key, Value>* r2, Node<Key, Value>* r1) const;
    void transformHelperLeft(rotateBST& t2, Node<Key, Value>* r2, Node<Key, Value>* r1) const;
 
};
 
template <typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const 
{
    //store keys of each tree in an unordered set
    std::unordered_set<Key> keys1;
    std::unordered_set<Key> keys2;
    getKeys(keys1, this -> mRoot);
    getKeys(keys2, t2.mRoot);
    
    //compare the two sets
    return keys1 == keys2;
}
 
template <typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const 
{
    //if the two trees don't have the same keys then stop
    if (!sameKeys(t2)) {
        return;
    }

    //go through each node and rotate right until there are no left children
    Node<Key, Value>* currNode = t2.mRoot;
    while (currNode != NULL) {
        while (currNode -> getLeft() != NULL) {
            t2.rightRotate(currNode);
            currNode = currNode -> getParent();
        }
        currNode = currNode -> getRight();
    }

    //call helper
    transformHelperRight(t2, t2.mRoot, this -> mRoot); 
}
template <typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r) 
{
    Node<Key, Value>* newRoot = r -> getRight();
    //stop if there is no right child
    if (newRoot == NULL) {
        return;
    }

    //perform rotation by changing left, right, parent pointers
    newRoot -> setParent(r -> getParent());
    Node<Key, Value>* parent = r -> getParent();
    if (parent != NULL){
        if (r == parent -> getLeft()){
            parent -> setLeft(newRoot);
        }
        else{
            parent -> setRight(newRoot);
        }
    }
    r -> setParent(newRoot);
    r -> setRight(newRoot -> getLeft());
    if (r -> getRight() != NULL) {
        r -> getRight() -> setParent(r);
    }
    newRoot -> setLeft(r);

    //set the new root if we rotated around the root
    if (this -> mRoot == r) {
        this -> mRoot = newRoot;
    }
}
 
template <typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r) 
{
    Node<Key, Value>* newRoot = r -> getLeft();
    //stop if there is no left child
    if (newRoot == NULL) {
        return;
    }

    //perform rotation by changing left, right, parent pointers
    newRoot -> setParent(r -> getParent());
    Node<Key, Value>* parent = r -> getParent();
    if (parent != NULL){
        if (r == r -> getParent() -> getLeft()){
            parent -> setLeft(newRoot);
        }
        else{
            parent -> setRight(newRoot);
        }
    }
    r -> setParent(newRoot);
    r -> setLeft(newRoot -> getRight());
    if (r -> getLeft() != NULL) {
        r -> getLeft() -> setParent(r);
    }
    newRoot -> setRight(r);

    //set the new root if we rotated around the root
    if (this -> mRoot == r) {
        this -> mRoot = newRoot;
    }
}
 
template <typename Key, typename Value>
void rotateBST<Key, Value>::getKeys(std::unordered_set<Key>& keys, Node<Key, Value>* r) const 
{
    //fills the set with all the keys in the tree
    if (r == NULL) {
        return;
    }

    //recursive call
    getKeys(keys, r -> getLeft());
    getKeys(keys, r -> getRight());
    keys.insert(r -> getKey());
}
 
template <typename Key, typename Value>
void rotateBST<Key, Value>::transformHelperRight(rotateBST& t2, Node<Key, Value>* r2, Node<Key, Value>* r1) const 
{
    //stop when a node is null
    if (r1 == NULL || r2 == NULL) {
        return;
    }

    //rotate left until the right node is in place
    while (r2 -> getKey() != r1 -> getKey()) {
        t2.leftRotate(r2);
        r2 = r2 -> getParent();
    }

    //recursive calls to left and right transforms
    transformHelperLeft(t2, r2 -> getLeft(), r1 -> getLeft());
    transformHelperRight(t2, r2 -> getRight(), r1 -> getRight());
}
 
template <typename Key, typename Value>
void rotateBST<Key, Value>::transformHelperLeft(rotateBST& t2, Node<Key, Value>* r2, Node<Key, Value>* r1) const 
{
    //stop when a node is null
    if (r1 == NULL || r2 == NULL) {
        return;
    }

    //rotate right until the right node is in place
    while (r2 -> getKey() != r1 -> getKey()) {
        t2.rightRotate(r2);
        r2 = r2 -> getParent();
    }

    //recursive calls to left and right transforms
    transformHelperLeft(t2, r2 -> getLeft(), r1 -> getLeft());
    transformHelperRight(t2, r2 -> getRight(), r1 -> getRight());
}
 
#endif
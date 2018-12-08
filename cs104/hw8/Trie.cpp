#include "Trie.h"

//create empty trieset
TrieSet::TrieSet()
:
_root(NULL)
{
}

//delete trieset
TrieSet::~TrieSet() {
	deleteNode(_root);
	delete _root;
}

//insert a word into trieset
void TrieSet::insert (std::string input) {
	if (_root == NULL) {
		_root = getChildNode(NULL);
	}

	struct TrieNode* node = _root;
	
	for (int i = 0; i < (int)input.size(); ++i){
		int index = input[i] - 'a';
		if (node -> children[index] == NULL) {
			node -> children[index] = getChildNode(node);
		}
		node = node -> children[index];
	}
	node -> inSet = true;
}

//remove word from trieset
void TrieSet::remove (std::string input) {
	struct TrieNode* node = prefix(input);
	if (node && node -> inSet == true) {
		node -> inSet = false;
		if (getChildNum(node) == 0) {
			TrieNode* parent = node -> parent;
			while (parent != NULL && getChildNum(parent) == 1) {
				node = parent;
				parent = node -> parent;
			}
			deleteNode(node);
		}
	}
}

//return node with the prefix
TrieNode* TrieSet::prefix(TrieNode* node, std::string px)
{
	if (node) {
		for (unsigned int i = 0; i < px.size(); ++i) {
			int index = px[i] - 'a';
			if (node -> children[index] == NULL) {
				return NULL;
			}
			node = node -> children[index];
		}
	}
	return node;
}

//return root of the trieset
TrieNode*  TrieSet::getRoot() {
	return _root;
}

//return the root of the prefix
TrieNode* TrieSet::prefix(std::string px) 
{
	return prefix(_root, px);
}

//get the child of the node
TrieNode* TrieSet::getChildNode(TrieNode* parent) const {
	struct TrieNode* node = new TrieNode;
	node -> inSet = false;
	node -> parent = parent;
	for (int i = 0; i < 26; ++i) {
		node -> children[i] = NULL;
	}
	return node;
}

//get the number of children of a node
int TrieSet::getChildNum(TrieNode* parent) const
{
	int count = 0;
	for (int i = 0; i < 26; ++i) {
		count += parent -> children[i] != NULL;
	}
	return count;
}

//delete all nodes
void TrieSet::deleteNode(TrieNode* node)
{
	if (node) {
		for (int i = 0; i < 26; ++i) {
			deleteNode(node -> children[i]);
		}

		TrieNode* parent = node -> parent;
		if (parent) {
			for (int i = 0; i < 26; ++i) {
				if (parent -> children[i] == node) {
					delete parent -> children[i];
					parent -> children[i] = NULL;
				}
			}
		}
		else {
			//delete node; //this must be the root
		}
	}
}
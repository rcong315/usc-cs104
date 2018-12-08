#ifndef TRAVERSAL_H
#define TRAVERSAL_H

#include <vector>

class Node {
public:
	Node(Node *left, Node *right, int val) {
		this->left = left;
		this->right = right;
		this->val = val;
	};

	Node* left;
	Node* right;
	int val;
};

void PreOrder(std::vector<int>& result, Node *start);
void InOrder(std::vector<int>& result, Node *start);
void PostOrder(std::vector<int>& result, Node *start);
void LevelOrder(std::vector<int>& result, Node *start);

bool checkSymmetrical(Node *root);

#endif
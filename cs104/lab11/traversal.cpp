#include "traversal.h"

//include what you need :D
#include <queue>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

void PreOrder(vector<int>& result, Node *start) {
	result.push_back(start -> val);
	if(start -> left != nullptr) {
	    PreOrder(result, start -> left);
	}
	if(start -> right != nullptr) {
        PreOrder(result, start -> right);
	}
}

void InOrder(vector<int>& result, Node *start) {
	if(start -> left != nullptr) {
	    InOrder(result, start -> left);
	}
	result.push_back(start -> val);
	if(start -> right != nullptr) {
        InOrder(result, start -> right);
	}
}

void PostOrder(vector<int>& result, Node *start) {
	if(start -> left != nullptr) {
	    PostOrder(result, start -> left);
	}
	if(start -> right != nullptr) {
        PostOrder(result, start -> right);
	}
    result.push_back(start -> val);
}

void LevelHelper(vector<int>& result, queue<Node*> queue) {
	if (queue.empty()) {
		return;
	}
	if (queue.front() -> left != nullptr) {
		queue.push(queue.front() -> left);
		result.push_back(queue.front() -> left -> val);
	}
	if (queue.front() -> right != nullptr) {
		queue.push(queue.front() -> right);
		result.push_back(queue.front() -> right -> val);
	}
	queue.pop();
	LevelHelper(result, queue);
}

//helper functions are encouraged :D
void LevelOrder(vector<int>& result, Node *start) {
	queue<Node*> queue;
	queue.push(start);
	result.push_back(start -> val);	
	if (queue.front() -> left != nullptr) {
		queue.push(queue.front() -> left);
		result.push_back(queue.front() -> left -> val);
	}
	if (queue.front() -> right != nullptr) {
		queue.push(queue.front() -> right);
		result.push_back(queue.front() -> right -> val);
	}
	queue.pop();
	LevelHelper(result, queue);
}

//helper functions are encouraged :D
bool checkSymmetrical(Node *root) {
	vector<int> result;
	stack<int> stack;
	LevelOrder(result, root);
	if (result.size() % 2 == 0) {
		return false;
	}
	result.erase(result.begin());
	while (!result.empty()) {
		if (!stack.empty() && result[0] == stack.top()) {
			stack.pop();
			result.erase(result.begin());
		}
		else {
			stack.push(result[0]);
			result.erase(result.begin());
		}
	}
	return stack.empty();
}


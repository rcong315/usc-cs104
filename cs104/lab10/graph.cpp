#include "graph.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

bool DFS(Node* start, Node* end) {
	stack<Node*> nodes;
	set<Node*> discovered;
	nodes.push(start);
	discovered.insert(start);
	while( !nodes.empty() ){
		Node* u = nodes.top();
		for( std::vector<Node*>::iterator it = u->neighbors.begin(); it != u->neighbors.end(); it++ ){
			if( *it == end ){
				return true;
			}
			else if( discovered.find(*it) == discovered.end() ){
				nodes.push(*it);
				discovered.insert(*it);
			}
		}
		nodes.pop();
	}
	return false;
}

bool BFS(vector<vector<int> > adjacency_matrix, int start, int end) {
	queue<int> nodes;
	set<int> discovered;
	nodes.push(start);
	discovered.insert(start);
	while( !nodes.empty() ){
		int u = nodes.front();
		for( unsigned int i = 0; i < adjacency_matrix[u].size(); i++ ){
			if( (i == (unsigned) end) & (adjacency_matrix[u][i] == 1) ){
				return true;
			}
			else if( (discovered.find(i) == discovered.end()) && (adjacency_matrix[u][i] == 1) ){
				nodes.push(i);
				discovered.insert(i);
			}
		}
		nodes.pop();
	}


	return false;
}
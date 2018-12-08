#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Node {
public:
    std::vector<Node*> neighbors;
};

bool DFS(Node* start, Node* end);
bool BFS(std::vector<std::vector<int> > adjacency_matrix, int start, int end);

#endif
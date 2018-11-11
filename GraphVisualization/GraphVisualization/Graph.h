#pragma once

#include <string>
#include <vector>

#include "Node.h"
#include "Edge.h"

class Graph {
public:
	Graph();
	~Graph();

	void readFromFile(std::string path);

public:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	std::vector<std::vector<bool>> adjacency;
};

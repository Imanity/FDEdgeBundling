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

	void randomLayout(double w, double h);
	void forceDirectedLayout(double w, double h, int niters);
	void edgeBundling();

public:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	std::vector<std::vector<Vec2>> subdivision_points;
};

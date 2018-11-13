#pragma once

#include <string>
#include <vector>
#include <iostream>

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

private:
	std::vector<Vec2> subdivide(std::vector<Vec2> &points, int n);
	double Ca(int, int);
	double Cs(int, int);
	double Cp(int, int);
	double Cv(int, int);
	Vec2 projectPointOnLine(Vec2 &, Vec2 &, Vec2 &);

public:
	std::vector<Node> nodes;
	std::vector<Edge> edges;
	std::vector<std::vector<Vec2>> subdivision_points;
};

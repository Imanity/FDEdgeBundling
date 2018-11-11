#include "Graph.h"

#include <fstream>

Graph::Graph() {
}

Graph::~Graph() {
}

void Graph::readFromFile(std::string path) {
	nodes.clear();
	edges.clear();

	std::ifstream nodeFile((path + "/nodes.txt").c_str());
	if (!nodeFile)
		return;
	int id = 0;
	while (!nodeFile.eof()) {
		long long uid;
		std::string username;
		nodeFile >> uid;
		if (nodeFile.eof())
			break;
		nodeFile >> username;
		nodes.push_back(Node(id, uid, username));
		id++;
	}
	nodeFile.close();

	std::ifstream edgeFile((path + "/edges.txt").c_str());
	if (!edgeFile)
		return;
	while (!edgeFile.eof()) {
		int uid1, uid2;
		edgeFile >> uid1;
		if (edgeFile.eof())
			break;
		edgeFile >> uid2;
		int id1 = -1, id2 = -1;
		for (int i = 0; i < nodes.size(); ++i) {
			if (nodes[i].uid == uid1) {
				id1 = i;
				break;
			}
		}
		for (int i = 0; i < nodes.size(); ++i) {
			if (nodes[i].uid == uid2) {
				id2 = i;
				break;
			}
		}
		if (id1 < 0 || id2 < 0)
			continue;
		if (id1 > id2) {
			int tmp = id1;
			id1 = id2;
			id2 = tmp;
		}
		edges.push_back(Edge(id1, id2));
	}
	edgeFile.close();
}

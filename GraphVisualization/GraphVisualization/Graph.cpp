#include "Graph.h"

#include <fstream>
#include <ctime>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

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

void Graph::randomLayout(double w, double h) {
	srand((unsigned)time(NULL));
	for (int i = 0; i < nodes.size(); ++i) {
		nodes[i].pos.x = rand() % (int)w;
		nodes[i].pos.y = rand() % (int)h;
	}
}

void Graph::forceDirectedLayout(double w, double h, int niters) {
	double area = w * h;
	double K = sqrt(area / (double)nodes.size());
	double t = w / 10.0;
	for (int i = 0; i < niters; ++i) {
		for (int j = 0; j < nodes.size(); ++j) {
			nodes[j].disp = Vec2(0, 0);
			for (int k = 0; k < nodes.size(); ++k) {
				if (j == k)
					continue;
				Vec2 delta = nodes[j].pos - nodes[k].pos;
				if (delta.len() == 0)
					delta = Vec2(1e-3, 1e-3);
				nodes[j].disp += (delta / delta.len()) * (K * K / delta.len());
			}
		}

		for (int j = 0; j < edges.size(); ++j) {
			Vec2 delta = nodes[edges[j].id1].pos - nodes[edges[j].id2].pos;
			if (delta.len() == 0)
				delta = Vec2(1e-3, 1e-3);
			Vec2 tmp = (delta / delta.len()) * (delta.len() * delta.len() / K);
			nodes[edges[j].id1].disp -= tmp;
			nodes[edges[j].id2].disp += tmp;
		}

		for (int j = 0; j < nodes.size(); ++j) {
			if (nodes[j].disp.len() == 0)
				nodes[j].disp = Vec2(1e-3, 1e-3);
			nodes[j].pos += (nodes[j].disp / nodes[j].disp.len()) * min(nodes[j].disp.len(), t);
			nodes[j].pos.x = min(w, max(0, nodes[j].pos.x));
			nodes[j].pos.y = min(h, max(0, nodes[j].pos.y));
		}
		t -= (w / 10.0) / niters;
		if (t < 1.0)
			return;
	}
}

void Graph::edgeBundling() {
	int C = 6;
	int P = 1;
	int I_initial = 90;
	double I_rate = 0.67;
	double S = 0.1;

	int I = I_initial;
	for (int cycle = 0; cycle < C; ++cycle) {
		for (int iteration = 0; iteration < I; ++iteration) {
			//
		}
		S /= 2.0;
		P *= 2;
		I = I_rate * I;
	}
}

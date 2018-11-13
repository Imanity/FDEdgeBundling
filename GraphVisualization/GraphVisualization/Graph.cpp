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
	double K = 0.1;
	int C = 6;
	int P = 1;
	int I_initial = 90;
	double I_rate = 0.67;
	double S = 0.1;
	double Ce_threshold = 0.4;

	subdivision_points.clear();
	for (int i = 0; i < edges.size(); ++i) {
		std::vector<Vec2> points;
		points.push_back(nodes[edges[i].id1].pos);
		points.push_back(nodes[edges[i].id2].pos);
		subdivision_points.push_back(points);
	}

	std::vector<std::vector<double>> Ce;
	for (int i = 0; i < edges.size(); ++i) {
		std::vector<double> ce;
		for (int j = 0; j < edges.size(); ++j) {
			if (i == j) {
				ce.push_back(1);
				continue;
			}
			ce.push_back(Ca(i, j) * Cs(i, j) * Cp(i, j) * Cv(i, j));
		}
		Ce.push_back(ce);
	}

	int I = I_initial;
	for (int cycle = 0; cycle < C; ++cycle) {
		for (int i = 0; i < subdivision_points.size(); ++i)
			subdivision_points[i] = subdivide(subdivision_points[i], P);
		for (int iteration = 0; iteration < I; ++iteration) {
			std::vector<std::vector<Vec2>> forces;
			for (int i = 0; i < edges.size(); ++i) {
				std::vector<Vec2> subdivision_forces;
				double kp = K / ((P + 1) * (subdivision_points[i][0] - subdivision_points[i][1]).len());
				for (int j = 0; j < P; ++j) {
					Vec2 Fs = (subdivision_points[i][j] - subdivision_points[i][j + 1]) * kp + (subdivision_points[i][j + 2] - subdivision_points[i][j + 1]) * kp;
					Vec2 Fe = Vec2(0, 0);
					for (int k = 0; k < edges.size(); ++k) {
						if (i == k || Ce[i][k] < Ce_threshold)
							continue;
						Vec2 dis = subdivision_points[k][j + 1] - subdivision_points[i][j + 1];
						if (dis.len() == 0)
							continue;
						Fe += dis / dis.len() *	Ce[i][k];
					}
					Vec2 force = Fs + Fe;
					subdivision_forces.push_back(force);
				}
				forces.push_back(subdivision_forces);
			}
			for (int i = 0; i < edges.size(); ++i) {
				for (int j = 0; j < P; ++j) {
					if (forces[i][j].len() == 0)
						continue;
					subdivision_points[i][j + 1] += (forces[i][j] / forces[i][j].len()) * S;
				}
			}
		}
		S /= 2.0;
		P *= 2;
		I = I_rate * I;
	}
}

std::vector<Vec2> Graph::subdivide(std::vector<Vec2> &points, int n) {
	std::vector<Vec2> sub_points;
	if (points.size() <= 1)
		return sub_points;

	double sum_distance = 0;
	for (int i = 0; i < points.size() - 1; ++i) {
		sum_distance += (points[i] - points[i + 1]).len();
	}
	double avg_distance = sum_distance / (n + 1);
	
	Vec2 start_pos = points[0];
	int end_id = 1;
	sub_points.push_back(start_pos);
	for (int i = 0; i < n; ++i) {
		double sub_distance = avg_distance;
		while ((start_pos - points[end_id]).len() < sub_distance) {
			sub_distance -= (start_pos - points[end_id]).len();
			start_pos = points[end_id];
			end_id++;
		}
		double r = sub_distance / (start_pos - points[end_id]).len();
		start_pos = start_pos + (points[end_id] - start_pos) * r;
		sub_points.push_back(start_pos);
	}
	sub_points.push_back(points[points.size() - 1]);
	return sub_points;
}

double Graph::Ca(int i, int j) {
	Vec2 P = nodes[edges[i].id2].pos - nodes[edges[i].id1].pos;
	Vec2 Q = nodes[edges[j].id2].pos - nodes[edges[j].id1].pos;
	return abs(P * Q / (P.len() * Q.len()));
}

double Graph::Cs(int i, int j) {
	Vec2 P = nodes[edges[i].id2].pos - nodes[edges[i].id1].pos;
	Vec2 Q = nodes[edges[j].id2].pos - nodes[edges[j].id1].pos;
	double lavg = (P.len() + Q.len()) / 2;
	return 2.0 / (lavg / min(P.len(), Q.len()) + max(P.len(), Q.len()) / lavg);
}

double Graph::Cp(int i, int j) {
	Vec2 P = nodes[edges[i].id2].pos - nodes[edges[i].id1].pos;
	Vec2 Q = nodes[edges[j].id2].pos - nodes[edges[j].id1].pos;
	double lavg = (P.len() + Q.len()) / 2;
	Vec2 Pm = (nodes[edges[i].id2].pos + nodes[edges[i].id1].pos) / 2;
	Vec2 Qm = (nodes[edges[j].id2].pos + nodes[edges[j].id1].pos) / 2;
	return lavg / (lavg + (Pm - Qm).len());
}

double Graph::Cv(int i, int j) {
	Vec2 P0 = nodes[edges[i].id1].pos;
	Vec2 P1 = nodes[edges[i].id2].pos;
	Vec2 Q0 = nodes[edges[j].id1].pos;
	Vec2 Q1 = nodes[edges[j].id2].pos;
	Vec2 Pm = (P0 + P1) / 2;
	Vec2 Qm = (Q0 + Q1) / 2;
	Vec2 I0 = projectPointOnLine(P0, P1, Q0);
	Vec2 I1 = projectPointOnLine(P0, P1, Q1);
	Vec2 Im = (I0 + I1) / 2;
	double VPQ = max(1.0 - 2.0 * (Pm - Im).len() / (I0 - I1).len(), 0);
	I0 = projectPointOnLine(Q0, Q1, P0);
	I1 = projectPointOnLine(Q0, Q1, P1);
	Im = (I0 + I1) / 2;
	double VQP = max(1.0 - 2.0 * (Qm - Im).len() / (I0 - I1).len(), 0);
	return min(VPQ, VQP);
}

Vec2 Graph::projectPointOnLine(Vec2 &p1, Vec2 &p2, Vec2 &q) {
	double l = (p1 - p2).len();
	double r = ((p1 - q) * (p1 - p2)) / (l * l);
	return p1 + (p2 - p1) * r;
}

#pragma once

#include <string>

class Node {
public:
	Node();
	Node(int, long long, std::string);
	~Node();

public:
	int id;
	long long uid;
	std::string username;

public:
	double x, y;
};

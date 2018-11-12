#pragma once

#include "Vec2.h"

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
	Vec2 pos;
	Vec2 disp;
};

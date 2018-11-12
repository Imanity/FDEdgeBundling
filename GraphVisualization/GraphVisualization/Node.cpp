#include "Node.h"

Node::Node() {
	//
}

Node::Node(int _id, long long u_id, std::string u_username) {
	id = _id;
	uid = u_id;
	username = u_username;
}

Node::~Node() {
	//
}

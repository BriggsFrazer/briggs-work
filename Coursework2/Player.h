#include <iostream>
#include <vector>
#include "Node.h"


class Player : public Node {
public:
	int destX;
	int destY;
	vector<Node> path;
};



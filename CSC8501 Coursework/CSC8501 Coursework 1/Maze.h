#ifndef Maze_H
#define Maze_H

#include <vector>
using namespace std;


class Maze {
public:
	int height;
	int width;
	int exits;
	vector<vector<char>> layout;

	Maze();
	void Reset();
	void makeCenter();
	void makeLayout();
	void makeExits();
	int makePath(int x, int y, int i, int j);
};

int mazeDisplay(Maze &maze);
Maze mazeGen(Maze &maze);
Maze findPath(Maze &maze);
#endif
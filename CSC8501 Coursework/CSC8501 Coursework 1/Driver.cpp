#include "FileIO.h"
#include "Maze.h"
#include <iostream>
using namespace std;

int main() {
	int height;
	int width;
	vector<vector<char>> currentMaze;


	MazeGen(1, 5, 5);
	MazeDisplay(currentMaze);

	
	
	// RETURNS 0 WHEN USER IS COMPLETE
	return 0;
}
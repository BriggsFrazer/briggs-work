#include "Maze.h"
#include <vector>
#include <iostream>
using namespace std;

int MazeDisplay(vector<vector<char>> maze){
	for (int i = 0; i < maze.size(); i++)
	{
		for (int j = 0; j < maze[i].size(); j++)
		{
			cout << maze[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
vector<vector<char>> MazeGen(int NumExits, int height, int width) {
	vector<vector<char>> vect(height, vector<char>(width));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			vect[i][j] = 'X';
		}
	}
	return vect;
}
vector<vector<char>> FindPath(vector<vector<char>> map) {
	vector<vector<char>> vect;
	return vect;
}
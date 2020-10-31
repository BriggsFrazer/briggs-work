#include "Maze.h"
#include <vector>
#include <iostream>
using namespace std;

int mazeDisplay(vector<vector<char>> maze){

	for (int i = 0; i < maze.size(); i++)
	{
		for (int j = 0; j < maze[i].size(); j++)
		{
			cout << maze[i][j];
		}
		cout << endl;
	}
	return 0;
}
vector<vector<char>> mazeGen() {
	int height;
	int width;
	int exits;

	//ADD VALIDATION
	cout << "Please enter an integer height" << endl;
	cin >> height;
	cout << "Please enter an integer width" << endl;
	cin >> width;
	cout << "Please enter an integer exits" << endl;
	cin >> exits;

	vector<vector<char>> vect(height, vector<char>(width));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			vect[i][j] = 'X';
		}
	}
	return vect;
}
vector<vector<char>> findPath(vector<vector<char>> maze) {

	return maze;
}
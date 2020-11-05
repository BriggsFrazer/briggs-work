#include "Maze.h"
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;

Maze::Maze() {
	Reset();
}

void Maze::Reset() {
	height = 0;
	width = 0;
	layout = vector<vector<char>>();
}

int Maze::makePath(int x, int y, int i, int j) {

	srand(time(0));
	//checks where the block is (if its on near the edge)
	char Start = 'S';
	char Exit = 'E';
	char Wall = 'X';
	char Open = ' ';

	//cout << "on space " << x << ',' << y << endl;
	if (layout[x + i][y + j] == Wall && layout[x + i + j][y + j + i] == Wall && layout[x + i - j][y + j - i] == Wall) {
		
		if (rand() % 100) {
			layout[x + i][y + j] = Open;
			//cout << "created path" << endl;
			return 1;
		}
	}
	

	return 0;

}

void Maze::makeCenter() {

	int centerPosX = height / 2;
	int centerPosY = width / 2;

	int rowNum[] = { 1,-1,0,0,1,-1,-1,1 };
	int columnNum[] = { 0,0,1,-1,1,-1,1,-1 };

	layout[centerPosX][centerPosY] = 'S';

	for (int i = 0; i < 8; i++) {
		layout[centerPosX + rowNum[i]][centerPosY + columnNum[i]] = ' ';
	}
}


void Maze::makeLayout() {
	char Start = 'S';
	char Exit = 'E';
	char Wall = 'X';
	char Open = ' ';

	int attempts = 5;
	int passageBuilt = 0;

	while (attempts > 0) {
		passageBuilt = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (layout[i][j] == Start || layout[i][j] == Open) {
					//If on the edge then dont do anything beyond this !!
					if (!(i == 1 || i == height - 2 || j == 1 || j == width - 2)) {
						passageBuilt += makePath(i, j, 1, 0) + makePath(i, j, -1, 0) + makePath(i, j, 0, 1) + makePath(i, j, 0, -1);

					}


				}
			}
		}
		if (passageBuilt == 0) {
			attempts -= 1;
		}
	}
}

void Maze::makeExits() {
	int exitCount = exits;
	int attempts = 5;
	srand(time(0));

	while (exitCount > 0 && attempts > 0) {
		int startCount = exitCount;
		for (int j = 0; j < width; j++) {
			if (layout[1][j] == ' ' && exitCount > 0 && layout[0][j] != 'E') {
				if (rand() % 100 > 50) {
					layout[0][j] = 'E';
					exitCount -= 1;
				}
			}
		}
		//check bottom
		for (int j = 0; j < width; j++) {
			if (layout[height - 2][j] == ' ' && exitCount > 0 && layout[height-1][j] != 'E') {
				if (rand() % 100 > 50) {
					layout[height - 1][j] = 'E';
					exitCount -= 1;
				}
			}
		}

		//check left
		for (int i = 0; i < height; i++) {
			if (layout[i][1] == ' ' && exitCount > 0 && layout[i][0] != 'E') {
				if (rand() % 100 > 50) {
					layout[i][0] = 'E';
					exitCount -= 1;
				}
			}
		}

		//check right
		for (int i = 0; i < height; i++ ) {
			if (layout[i][width - 2] == ' ' && exitCount > 0 && layout[i][width-1] != 'E') {
				if (rand() % 100 > 50) {
					layout[i][width - 1] = 'E';
					exitCount -= 1;
				}
			}

		}
		if (startCount == exitCount) {
			attempts -= 1;
		}
	}
}

int mazeDisplay(Maze &maze){

	for (int i = 0; i < maze.layout.size(); i++)
	{
		for (int j = 0; j < maze.layout[i].size(); j++)
		{
			cout << maze.layout[i][j];
		}
		cout << endl;
	}
	return 0;
}
Maze mazeGen(Maze &maze) {
	//ADD VALIDATION
	cout << "Please enter an integer height" << endl;
	cin >> maze.height;
	cout << "Please enter an integer width" << endl;
	cin >> maze.width;
	cout << "Please enter an integer exits" << endl;
	cin >> maze.exits;

	vector<vector<char>> vect(maze.height, vector<char>(maze.width));



	for (int i = 0; i < maze.height; i++) {
		for (int j = 0; j < maze.width; j++) {
			vect[i][j] = 'X';
		}
	}

	maze.layout = vect;


	maze.makeCenter();
	maze.makeLayout();
	maze.makeExits();

	return maze;
}
Maze findPath(Maze &maze ) {

	//breadth first search
	int rowNum[] = {-1,0,0,1};
	int columnNum[] = {0,-1,1,0};

	int INFINITY;
	//Loop through maze and find start and end points
	pair<int, int> start;
	vector<pair<int,int>> endPoints;

	vector<vector<bool>> visited(maze.height, vector<bool>(maze.width));

	vector<vector<int>> weights(maze.height, vector<int>(maze.width));
	
	vector<pair<int, int>> queue;

	vector<pair<int,int>> path;

	for (int i = 0; i < maze.height; i++) {
		for (int j = 0; j < maze.width; j++) {
			if (maze.layout[i][j] == 'S') {
				start = make_pair(i, j);
			}
			if (maze.layout[i][j] == 'E') {
				endPoints.push_back(make_pair(i, j));
				
			}
		}
	}




	for (int ends = 0; ends < endPoints.size(); ends++){
		visited[start.first][start.second] = true;
		weights[start.first][start.second] = 0;
		queue.push_back(start);

		

		while (!queue.empty()) {
			pair<int, int> curNode = queue.front();
			queue.pop_back();
			int i = curNode.first;
			int j = curNode.second;
			int dist = weights[i][j];

			if (i == endPoints[ends].first && j == endPoints[ends].second) {
				for (j = 0; j < queue.size(); j++) {
					
					maze.layout[queue[j].first][queue[j].second] = 'o';
				}
				cout << "found the end";
				break;
			}

			for (int k = 0; k < 4; k++) {
				//ISSUE IN THIS IF
				if (maze.layout[i + rowNum[k]][j + columnNum[k]] != 'X' && !visited[i + rowNum[k]][j + columnNum[k]]) {
					visited[i + rowNum[k]][j + columnNum[k]] = true;
					queue.push_back(make_pair((i + rowNum[k]), (i + columnNum[k])));
					path.push_back(make_pair((i + rowNum[k]), (i + columnNum[k])));
					weights[i + rowNum[k]][j + rowNum[k]] = dist + 1;
				}
			}

		}

	}


	return maze;
}
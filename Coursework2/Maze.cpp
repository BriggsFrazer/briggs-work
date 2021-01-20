#include "Maze.h"
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>
#include <time.h>
#include <windows.h>


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
	char Start = 'F';
	char Exit = 'E';
	char Wall = 'X';
	char Open = ' ';

	if (layout[x + i][y + j] == Wall && layout[x + i + j][y + j + i] == Wall && layout[x + i - j][y + j - i] == Wall) {
		layout[x + i][y + j] = Open;
		return 1;
	}


	return 0;

}

void Maze::makeCenter() {

	int centerPosX = height / 2;
	int centerPosY = width / 2;

	int rowNum[] = { 1,-1,0,0,1,-1,-1,1 };
	int columnNum[] = { 0,0,1,-1,1,-1,1,-1 };

	layout[centerPosX][centerPosY] = 'F';

	for (int i = 0; i < 8; i++) {
		layout[centerPosX + rowNum[i]][centerPosY + columnNum[i]] = ' ';
	}
}


void Maze::makeLayout() {
	char Start = 'F';
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
		for (int j = 0; j < width; j++) {
			if (layout[height - 2][j] == ' ' && exitCount > 0 && layout[height - 1][j] != 'E') {
				if (rand() % 100 > 50) {
					layout[height - 1][j] = 'E';
					exitCount -= 1;
				}
			}
		}
		for (int i = 0; i < height; i++) {
			if (layout[i][1] == ' ' && exitCount > 0 && layout[i][0] != 'E') {
				if (rand() % 100 > 50) {
					layout[i][0] = 'E';
					exitCount -= 1;
				}
			}
		}
		for (int i = 0; i < height; i++) {
			if (layout[i][width - 2] == ' ' && exitCount > 0 && layout[i][width - 1] != 'E') {
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

	if (exitCount != 0) {
		cout << "Unable to place all exits, likely that there were not enough valid locations";
	}

}

bool Maze::isValid(int x, int y) {
	if (x < 0 || y < 0 || x > height || y > width) {
		return false;
	}
	if (layout[x][y] == 'X' || layout[x][y] == 'E') {
		return false;
	}
	return true;
}

bool isDestination(int x, int y, Node dest) {
	if (x == dest.x && y == dest.y) {
		return true;
	}
	return false;
}

double calculateH(int x, int y, Node dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x) + (y - dest.y) * (y - dest.y)));
	return H;
}

vector<Node> aStar(Player player, Maze& maze) {
	vector<Node> empty;
	Node dest;
	dest.x = player.destX;
	dest.y = player.destY;

	vector<vector<bool>> closedList(maze.height, vector<bool>(maze.width));

	//Converting all map characters into Nodes
	vector<vector<Node>> weightedMap(maze.height, vector<Node>(maze.width));
	for (int x = 0; x < (maze.height); x++) {
		for (int y = 0; y < (maze.width); y++) {
			weightedMap[x][y].fCost = FLT_MAX;
			weightedMap[x][y].gCost = FLT_MAX;
			weightedMap[x][y].hCost = FLT_MAX;
			weightedMap[x][y].parentX = -1;
			weightedMap[x][y].parentY = -1;
			weightedMap[x][y].x = x;
			weightedMap[x][y].y = y;
		}
	}

	int x = player.x;
	int y = player.y;
	weightedMap[x][y].fCost = 0.0;
	weightedMap[x][y].gCost = 0.0;
	weightedMap[x][y].hCost = 0.0;
	weightedMap[x][y].parentX = x;
	weightedMap[x][y].parentY = y;

	vector<Node> openList;
	openList.emplace_back(weightedMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < maze.height * maze.width) {
		Node node;
		do {
			float temp = FLT_MAX;
			vector<Node>::iterator itNode;
			for (vector<Node>::iterator it = openList.begin(); it != openList.end(); it = next(it)) {
				Node n = *it;
			if (n.fCost < temp) {
				temp = n.fCost;
				itNode = it;
			}
		}
		node = *itNode;
		openList.erase(itNode);

		} while (maze.isValid(node.x, node.y) == false);

		x = node.x;
		y = node.y;

		int rowNum[] = { -1,0,0,1 };
		int columnNum[] = { 0,-1,1,0 };

		for (int k = 0; k < 4; k++) {
			double gNew, hNew, fNew;
			if (maze.isValid(x + rowNum[k], y + columnNum[k])) {
				if (isDestination(x + rowNum[k], y + columnNum[k], dest)) {
					weightedMap[x + rowNum[k]][y + columnNum[k]].parentX = x;
					weightedMap[x + rowNum[k]][y + columnNum[k]].parentY = y;
					destinationFound = true;
					return makePath(weightedMap, dest);
				}
				else if (closedList[x + rowNum[k]][y + columnNum[k]] == false) {
					gNew = node.gCost + 1.0;
					hNew = calculateH(x + rowNum[k], y + columnNum[k], dest);
					fNew = gNew + hNew;
					if (weightedMap[x + rowNum[k]][y + columnNum[k]].fCost == FLT_MAX || weightedMap[x + rowNum[k]][y + columnNum[k]].fCost > fNew) {
						weightedMap[x + rowNum[k]][y + columnNum[k]].fCost = fNew;
						weightedMap[x + rowNum[k]][y + columnNum[k]].gCost = gNew;
						weightedMap[x + rowNum[k]][y + columnNum[k]].hCost = hNew;
						weightedMap[x + rowNum[k]][y + columnNum[k]].parentX = x;
						weightedMap[x + rowNum[k]][y + columnNum[k]].parentY = y;
						openList.emplace_back(weightedMap[x + rowNum[k]][y + columnNum[k]]);

				}
			}
		}
	}

}
if (destinationFound == false) {
	cout << "Destination not found" << endl;
	return empty;
}

}

vector<Node> makePath(vector<vector<Node>> weightedMap, Node dest) {
	try {
		cout << "Found a path" << endl;
		int x = dest.x;
		int y = dest.y;
		stack<Node> path;
		vector<Node> usablePath;
		while (!(weightedMap[x][y].parentX == x && weightedMap[x][y].parentY == y) && weightedMap[x][y].x != -1 && weightedMap[x][y].y != -1) {
			path.push(weightedMap[x][y]);
			int tempX = weightedMap[x][y].parentX;
			int tempY = weightedMap[x][y].parentY;
			x = tempX;
			y = tempY;
		}
		path.push(weightedMap[x][y]);
		while (!path.empty()) {
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		return usablePath;
	}
	catch (const exception & e) {
		cout << e.what() << endl;
	}
}

int mazeDisplay(Maze& maze, vector<Player> playerList) {

	vector<pair<int, int>> playerLocations;
	for (int i = 0; i < playerList.size(); i++) {
		playerLocations.emplace_back(make_pair(playerList[i].x, playerList[i].y));
	}



	for (int i = 0; i < maze.layout.size(); i++)
	{
		for (int j = 0; j < maze.layout[i].size(); j++)
		{
			if ((find(playerLocations.begin(), playerLocations.end(), make_pair(i, j)) != playerLocations.end())){
				cout << "P";
			}
			else {
				cout << maze.layout[i][j];
			}
		}
		cout << endl;
	}
	return 0;
}
Maze mazeGen(Maze& maze) {

	do{
		cout << "Please enter an integer height (5 or more and less than 30)" << endl;
		cin >> maze.height;
	} while (!(maze.height >= 5 && maze.height <= 30));

	do {
		cout << "Please enter an integer width (5 or more and less than 30)" << endl;
		cin >> maze.width;
	} while (!(maze.width >= 5 && maze.width <= 30));

	do {
		cout << "Please enter an integer exits. At least one! " << endl;
		cin >> maze.exits;
	} while (!(maze.exits < ((maze.height * 2) + (maze.width * 2) - 4) / 2 && maze.exits > 0));
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

vector<Player> generatePlayers(Maze& maze) {
	vector<Player> playerList;
	int playerCount;
	vector<pair<int, int>> startPoints;
	pair<int, int> end;
	int height = maze.height;
	int width = maze.width;

	for (int i = 0; i < maze.layout.size(); i++)
	{
		for (int j = 0; j < maze.layout[i].size(); j++)
		{
			if (maze.layout[i][j] == 'E') {
				startPoints.emplace_back(make_pair(i, j));
			}
			if (maze.layout[i][j] == 'F') {
				end = make_pair(i, j);
			}
		}
	}

	do {
		cout << "How many players would you like? At least one and no more than the number of exits" << endl;
		cin >> playerCount;
	} while (!(playerCount > 0 && playerCount <= startPoints.size()));

	for (int i = 0; i < playerCount; i++) {
		playerList.emplace_back(createPlayer(startPoints.front(), end, maze));
		startPoints.erase(startPoints.begin());
	}
	return playerList;
}

Player createPlayer(pair<int, int> start, pair<int, int> end, Maze &maze) {
	Player p;
	if (start.first == 0) {
		p.x = 1;
		p.y = start.second;
	}
	if (start.first == maze.height-1) {
		p.x = maze.height -2;
		p.y = start.second;
	}
	if (start.second == 0) {
		p.y = 1;
		p.x = start.first;
	}
	if (start.second == maze.width-1) {
		p.y = maze.width -2;
		p.x = start.first;
	}


	p.destX = end.first;
	p.destY = end.second;

	return p;
}

void generatePaths(Maze& maze, vector<Player>& playerList) {
	for (int i = 0; i < playerList.size(); i++) {
		playerList[i].path = aStar(playerList[i], maze);
		playerList[i].path.erase(playerList[i].path.begin());
	}
}

bool playerStep(Maze& maze, vector<Player>& playerList) {
	vector<pair<int, int>> playerLocations;
	int movesMade = 0;

	//removes all players that are at the end
	playerList.erase(remove_if(playerList.begin(), playerList.end(), [](Player const& p) {return (p.x == p.destX && p.y == p.destY); }),playerList.end());

	for (int i = 0; i < playerList.size(); i++) {
		if (playerList[i].path.size() > 0) {
			for (int i = 0; i < playerList.size(); i++) {
				playerLocations.emplace_back(make_pair(playerList[i].x, playerList[i].y));
			}
			if (!(find(playerLocations.begin(), playerLocations.end(), make_pair(playerList[i].path.front().x, playerList[i].path.front().y))  != playerLocations.end())) {
				playerList[i].x = playerList[i].path.front().x;
				playerList[i].y = playerList[i].path.front().y;
				playerList[i].path.erase(playerList[i].path.begin());
				movesMade += 1;
			}
		}
	}

	if (movesMade == 0 && playerLocations.size() != 0) {
		return true;
	}

	if (movesMade != playerLocations.size()) {
		cout << "Livelock has occurred" << endl;
	}

	mazeDisplay(maze, playerList);
	cout << endl;
	Sleep(500);
	return false;
}


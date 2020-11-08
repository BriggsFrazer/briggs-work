
#ifndef Maze_H
#define Maze_H

#include <vector>
#include "Player.h"

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
	bool isValid(int x, int y);
	int makePath(int x, int y, int i, int j);
};

int mazeDisplay(Maze& maze, vector<Player> playerList);
Maze mazeGen(Maze& maze);
double calculateH(int x, int y, Node dest);
bool isDestination(int x, int y, Node dest);
vector<Node> makePath(vector<vector<Node>> weightedMap, Node dest);
vector<Node> aStar(Player player, Node dest, Maze& maze);
double calculateH(int x, int y, Node dest);
vector<Player> generatePlayers(Maze& maze);
Player createPlayer(pair<int, int> start, pair<int, int> end, Maze& maze);
void generatePaths(Maze& maze, vector<Player>& playerList);
bool playerStep(Maze& maze, vector<Player>& playerList);

#endif
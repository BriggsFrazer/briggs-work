#include "FileIO.h"
#include "Maze.h"

#include <iostream>
using namespace std;


int preMazeMenu(Maze &currentMaze) {
	int choice = 0;
	cout << "[1] : Generate maze" << endl;
	cout << "[2] : Load maze" << endl;
	cout << "[0] : Quit" << endl;
	cin >> choice;
	switch (choice) {
	case 1:
		cout << "Generating maze.." << endl;
		currentMaze = mazeGen(currentMaze);
		return 1;
	case 2:
		cout << "Loading maze.." << endl;
		currentMaze = loadFile(currentMaze);
		return 1;
	case 0:
		cout << "Qutting.." << endl;

		return 0;
	default:
		cout << "Enter a valid menu option" << endl;
	}
}

int fullMenu(Maze& currentMaze,vector<Player>& playerList) {
	int choice = 0;
	bool deadlock = false;
	cout << "[1] : Generate maze" << endl;
	cout << "[2] : Load maze" << endl;
	cout << "[3] : Save maze" << endl;
	cout << "[4] : Add players" << endl;
	cout << "[5] : Display maze" << endl;
	cout << "[6] : Show player routes" << endl;
	cout << "[0] : Quit" << endl;
	cin >> choice;
	switch (choice) {
	case 1:
		cout << "Generating maze.." << endl;
		currentMaze = mazeGen(currentMaze);
		return 1;
	case 2:
		cout << "Loading maze.." << endl;
		currentMaze = loadFile(currentMaze);
		return 1;
	case 3:
		cout << "Saving maze.." << endl;
		saveFile(currentMaze);
		return 1;
	case 4:
		cout << "Adding players.." << endl;
		playerList = generatePlayers(currentMaze);
		return 1;
	case 5:
		cout << "Display maze.." << endl;
		mazeDisplay(currentMaze, playerList);
		return 1;
	case 6:
		cout << "Showing player routes maze.." << endl;
		generatePaths(currentMaze,playerList);

		while (playerList.size() > 0 && deadlock == false) {
			deadlock = playerStep(currentMaze, playerList);
		}
		if (deadlock == true) {
			cout << "Maze resulted in a deadlock" << endl;
		}
		if (deadlock == false) {
			cout << "Maze is solvable (if livelock occured then only partially)" << endl;
		}
		return 1;
	case 0:
		cout << "Qutting.." << endl;

		return 0;
	default:
		cout << "Enter a valid menu option" << endl;
	}
}

int main() {

	int choice;
	Maze currentMaze;
	vector<Player> playerList;

	do {
		currentMaze.layout.size() == 0 ? cout << "Maze loaded: NONE" << endl : cout << "Maze currently loaded" << endl;
		currentMaze.layout.size() == 0 ? choice = preMazeMenu(currentMaze) : choice = fullMenu(currentMaze,playerList);

	} while (choice != 0);
	return 0;


	return 0;
}


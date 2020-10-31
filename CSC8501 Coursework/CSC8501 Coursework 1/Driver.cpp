#include "FileIO.h"
#include "Maze.h"
#include <iostream>
using namespace std;

int main() {

	vector<vector<char>> currentMaze;
	char hasMaze;
	char saveMaze;

	cout << "Do you have a maze to load? [Y] or [N]" << endl;
	cin >> hasMaze;
	while (hasMaze != 'Y' && hasMaze != 'N') {
		cout << "Please enter [Y] or [N]" << endl;
		cin >> hasMaze;
	}
	currentMaze = (hasMaze == 'N') ? mazeGen() : loadFile();
	system("cls");

	mazeDisplay(&currentMaze);

	cout << "Do you want to save the maze to a new file? [Y] or [N]" << endl;
	cin >> saveMaze;
	while (saveMaze != 'Y' && saveMaze != 'N') {
		cout << "Please enter [Y] or [N]" << endl;
		cin >> saveMaze;
	}

	saveFile(&currentMaze);
	//saving should be done here


	cout << "Here is the solved maze: ";
	currentMaze = findPath(currentMaze);
	mazeDisplay(&currentMaze);
	
	// RETURNS 0 WHEN USER IS COMPLETE
	return 0;
}
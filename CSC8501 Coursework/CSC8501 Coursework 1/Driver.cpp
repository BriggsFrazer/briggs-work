#include "FileIO.h"
#include "Maze.h"
#include <iostream>
using namespace std;

int main() {

	vector<vector<char>> currentMaze;
	char hasMaze;
	char saveMaze;
	char repeat;

	do {

		cout << "Do you have a maze to load? [Y] or [N]" << endl;
		cin >> hasMaze;
		while (hasMaze != 'Y' && hasMaze != 'N') {
			cout << "Please enter [Y] or [N]" << endl;
			cin >> hasMaze;
		}
		currentMaze = (hasMaze == 'N') ? mazeGen() : loadFile();
		

		mazeDisplay(currentMaze);

		cout << "Do you want to save the maze to a new file? [Y] or [N]" << endl;
		cin >> saveMaze;
		while (saveMaze != 'Y' && saveMaze != 'N') {
			cout << "Please enter [Y] or [N]" << endl;
			cin >> saveMaze;
		}

		saveFile(currentMaze);
		//saving should be done here
		//system("cls");

		cout << "Here is the solved maze: " << endl;
		currentMaze = findPath(currentMaze);
		mazeDisplay(currentMaze);

		cout << "Do you want to go again? [Y] or [N]" << endl;
		cin >> repeat;
		while (repeat != 'Y' && repeat != 'N') {
			cout << "Please enter [Y] or [N]" << endl;
			cin >> repeat;
		}

	}

	while (repeat != 'N');
	
	// RETURNS 0 WHEN USER IS COMPLETE
	return 0;
}
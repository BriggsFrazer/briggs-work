#include "FileIO.h"
#include "Maze.h"
#include <iostream>
using namespace std;

int main() {

	
	char hasMaze;
	char saveMaze;
	char repeat;

	do {
		Maze currentMaze;
		cout << "Do you have a maze to load? [Y] or [N]" << endl;
		cin >> hasMaze;
		while (hasMaze != 'Y' && hasMaze != 'N') {
			cout << "Please enter [Y] or [N]" << endl;
			cin >> hasMaze;
		}
		currentMaze = (hasMaze == 'N') ? mazeGen(currentMaze) : loadFile(currentMaze);
		

		mazeDisplay(currentMaze);

		cout << "Do you want to save the maze to a new file? [Y] or [N]" << endl;
		cin >> saveMaze;
		while (saveMaze != 'Y' && saveMaze != 'N') {
			cout << "Please enter [Y] or [N]" << endl;
			cin >> saveMaze;
		}

		if (saveMaze == 'Y') 
			saveFile(currentMaze); cout << "hello";
		


		cout << "Here is the solved maze: " << endl;
		currentMaze = findPath(currentMaze);
		mazeDisplay(currentMaze);

		cout << "Do you want to go again? [Y] or [N]" << endl;
		cin >> repeat;
		while (repeat != 'Y' && repeat != 'N') {
			cout << "Please enter [Y] or [N]" << endl;
			cin >> repeat;
		}

		currentMaze.Reset();
	}

	while (repeat != 'N');
	
	return 0;
}
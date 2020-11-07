#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "FileIO.h";


using namespace std; 

Maze loadFile(Maze &loadedMaze) {
	string fileName;
	ifstream file;


	cout << "What is the name of your file?";
	cin >> fileName;
	file.exceptions(ifstream::badbit);


	file.open(fileName);
	if (!file.is_open()) {
		cout << "ERROR OPENING FILE" << endl;
		return loadedMaze;
	}


	for (string line; getline(file, line);) {
		vector<char> temp;
		for (int i = 0; i < line.size();i++) {
			temp.push_back(line.at(i));
		}
		loadedMaze.layout.push_back(temp);
		temp.clear();
	}

	loadedMaze.height = loadedMaze.layout.size();
	loadedMaze.width = loadedMaze.layout[0].size();

	if (!checkMaze(loadedMaze)) {
		cout << "Invalid maze loaded, maze cannot be loaded" << endl;
		loadedMaze.layout.clear();
		return loadedMaze;
	}

	file.close();
	return loadedMaze;
	
}

bool checkMaze(Maze &maze) {
	int startCount = 1;
	for (int i = 0; i < maze.layout.size(); i++) {
		for (int j = 0; j < maze.layout[i].size(); j++) {
			if (maze.layout[i][j] == 'S') {
				startCount -= 1;
			}
			if (maze.layout[i][j] != 'X' && maze.layout[i][j] != 'E' && maze.layout[i][j] != 'S' && maze.layout[i][j] != ' ') {
				cout << "Invailid character found when reading maze WITH INVALID CHARACTER " << maze.layout[i][j] << endl;
				return false;
			}
			if (maze.layout[i].size() != maze.width) {
				cout << "Maze is not rectangular" << endl;
				return false;
			}
		}
	}
	if (!checkMazeWalls(maze)) {
		cout << "Maze wall is incorrect" << endl;
		return false;
	}

	if (startCount != 0) {
		cout << "Incorrect number of start points in the maze" << endl;
		return false;
	}


	return true;
}

bool checkMazeWalls(Maze& maze) {
	int rowBound[] = {0,maze.height -1 };
	int columnBound[] = { 0, maze.width -1};

	for (int i = 0; i < maze.width; i++) {
		for (int j = 0; j < 2; j++) {
			if (maze.layout[rowBound[j]][i] != 'X' && maze.layout[rowBound[j]][i] != 'E') {
				cout << "IN UP DOWN FOUND IN WALL " << maze.layout[j][i] << " AT COORDS " << j << ',' << i;
				return false;
			}
		}
	}
	for (int i = 0; i < maze.height; i++) {
		for (int j = 0; j < 2; j++) {
			if (maze.layout[i][columnBound[j]] != 'X' && maze.layout[i][columnBound[j]] != 'E') {
				cout << "IN LEFT RIGHT FOUND IN WALL " << maze.layout[j][i] << " AT COORDS " << i << ',' << j;
				cout << "FOUND IN WALL " << maze.layout[j][i];
				return false;
			}
		}
	}

	return true;
}

int saveFile(Maze &maze) {
	string fileName;
	
	cout << "Enter the file name: ";
	cin >> fileName;

	ofstream file;
	file.open(fileName);

	if (!file) {
		perror("The following error occured ");
	}





	for (int i = 0; i < maze.layout.size(); i++) {
		string temp = "";
		for (int j = 0; j < maze.layout[i].size(); j++) {
			
			temp += maze.layout[i][j];
		}
		file << temp << endl;
	}

	
	
	file.close();

	return 0;
}
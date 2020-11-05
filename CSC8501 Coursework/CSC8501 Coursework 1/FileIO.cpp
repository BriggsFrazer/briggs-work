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
	//NEEDS TO BE VALIDATED

	file.open(fileName);

	for (string line; getline(file, line);) {
		vector<char> temp;
		for (int i = 0; i < line.size();i++) {
			temp.push_back(line.at(i));
		}
		loadedMaze.layout.push_back(temp);
		temp.clear();
	}

	file.close();
	return loadedMaze;
	
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
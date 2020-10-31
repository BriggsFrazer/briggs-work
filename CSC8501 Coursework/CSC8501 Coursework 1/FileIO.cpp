#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "FileIO.h";

using namespace std; 

vector<vector<char>> loadFile() {
	string fileName;
	ifstream file;
	vector<vector<char>> loadedVect;


	cout << "What is the name of your file?";
	cin >> fileName;
	//NEEDS TO BE VALIDATED

	file.open(fileName);

	for (string line; getline(file, line);) {
		vector<char> temp;
		for (int i = 0; i < line.size();i++) {
			temp.push_back(line.at(i));
		}
		loadedVect.push_back(temp);
		temp.clear();
	}

	file.close();
	return loadedVect;
	
}

int saveFile(vector<vector<char>>  maze) {
	string fileName;
	
	cout << "Enter the file name: ";
	cin >> fileName;



	ofstream file;
	file.open(fileName);
	file << "wow";

	for (int i = 0; i < maze.size(); i++) {
		string temp = "";
		for (int j = 0; j < maze[i].size(); j++) {
			temp += maze[i][j];
		}
		file << temp << '/n';
	}

	
	file.close();

	return 0;
}
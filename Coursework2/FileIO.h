#include <vector>
#include "Maze.h"
using namespace std;


Maze loadFile(Maze& loadedMaze);

int saveFile(Maze& maze);

bool checkMaze(Maze& maze);
bool checkMazeWalls(Maze& maze);

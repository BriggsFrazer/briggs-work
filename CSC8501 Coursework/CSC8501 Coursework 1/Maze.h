#include <vector>
using namespace std;

int MazeDisplay(vector<vector<char>> maze);
vector<vector<char>> MazeGen(int NumExits, int height, int width);
vector<vector<char>> FindPath(vector<vector<char>> map);

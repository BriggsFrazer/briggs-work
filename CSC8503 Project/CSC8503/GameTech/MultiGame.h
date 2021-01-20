#pragma once
#include "SingleGame.h"
class MultiGame : public SingleGame {
public: 
	MultiGame();
	
	~MultiGame() {};


	void InitLevelGeometry();
	void InitWorld();

	void InitWalls();
	void QuaterWalls();
	void InitFloor();
	void InitSticky();

	aiPlayerObject* InitAI(Vector3 position);

protected:
	Vector2 gridSquare = Vector2(10, 10);
};
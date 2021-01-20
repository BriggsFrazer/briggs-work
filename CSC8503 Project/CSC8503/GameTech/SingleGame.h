#pragma once
#include "BaseGame.h"

class SingleGame : public BaseGame {
public:
	SingleGame() ;
	~SingleGame() {};

	void InitWorld();

	playerObject* InitPlayer(Vector3 position);

	virtual void InitLevelGeometry();
	GameObject* AddGround(Vector3 position, Vector3 size, string name, Vector4 colour);
	void AddCubeWall(Vector3 startPos, int width, int height);
	void AddBallPit(Vector3 startPos, int height, int width);

	GameObject* AddDeathBarrier(Vector3 size);

	

	void DisplayText();

protected:

};

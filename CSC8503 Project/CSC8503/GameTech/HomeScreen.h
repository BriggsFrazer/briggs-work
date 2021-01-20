#pragma once
#include "BaseGame.h"

class HomeScreen : public BaseGame {
public:
	HomeScreen();
	~HomeScreen() {};

	void InitScene();
	void InitWorld();
	void InitCamera();
	void InitMenuBlocks();

	void UpdateGame(float dt);

	void DisplayText();



protected:



};
#pragma once
#include "../CSC8503Common/PushdownState.h"
#include "../CSC8503Common/PushdownMachine.h"

#include "../../Common/Window.h"


using namespace NCL;
using namespace CSC8503;


class PauseScreen : public PushdownState {
	BaseGame*& currentScene;
	vector<BaseGame*>& scenes;
public:


	PauseScreen(BaseGame*& scene, vector<BaseGame*>& sceneList) : currentScene(scene), scenes(sceneList) {

	}

	PushdownResult OnUpdate(float dt, PushdownState** newState) override {

		unpauseTimer += dt;
		currentScene->GetRenderer()->DrawString("PAUSED", Vector2(10, 10));
		currentScene->GetRenderer()->DrawString("[ESC] TO UNPAUSE", Vector2(10, 20));


		if (unpauseTimer > delay) {
			if (Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
				return PushdownResult::Pop;
			}
		}


		return PushdownResult::NoChange;
	}
	void OnAwake() override {
		currentScene->Pause(true);
	}

protected:
	float unpauseTimer = 0;
	float delay = 0.2f;

};


class LoseScreen : public PushdownState {
	BaseGame*& currentScene;
	vector<BaseGame*>& scenes;
public:


	LoseScreen(BaseGame*& scene, vector<BaseGame*>& sceneList) : currentScene(scene), scenes(sceneList) {

	}

	PushdownResult OnUpdate(float dt, PushdownState** newState) override {
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::R)) {
			std::cout << "Returning to main menu! \n";
			return PushdownResult::Pop;
		}


		for (playerObject* p : currentScene->GetPlayerList()) {
			if (p->GetName() == "player") {

				currentScene->GetRenderer()->DrawString("YOU LOSE! TRY AGAIN NEXT TIME", Vector2(10, 10));
				currentScene->GetRenderer()->DrawString("PRESS R TO RETRY", Vector2(10, 20));

			}
		}
		return PushdownResult::NoChange;
	}
	void OnAwake() override {

		currentScene->setIsComplete(true);
		currentScene->Pause(true);
	}


};


class WinScreen : public PushdownState {
	BaseGame*& currentScene;
	vector<BaseGame*>& scenes;
public:


	WinScreen(BaseGame*& scene, vector<BaseGame*>& sceneList) : currentScene(scene), scenes(sceneList) {

	}

	PushdownResult OnUpdate(float dt, PushdownState** newState) override {
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::R)) {
			return PushdownResult::Pop;
		}
		for (playerObject* p : currentScene->GetPlayerList()) {
			if (p->GetHasWon() == true && p->GetName() == "player") {
				currentScene->GetRenderer()->DrawString("CONGRATULATIONS YOU WON!", Vector2(10, 10));
				string score = std::to_string(p->GetScore());
				string coins = std::to_string(p->GetCoins());
				currentScene->GetRenderer()->DrawString("Final Score: " + score + " Coins:" + coins + "/10!", Vector2(10, 20));
			}
			else {
				currentScene->GetRenderer()->DrawString("TRY AGAIN NEXT TIME", Vector2(10, 10));

			}
			currentScene->GetRenderer()->DrawString("Press R to Reset! ", Vector2(10, 30));
		}

		

		return PushdownResult::NoChange;
	}
	void OnAwake() override {
		currentScene->Pause(true);
	}


};

class SinglePlayerScene : public PushdownState {
	BaseGame*& currentScene;
	vector<BaseGame*>& scenes;
public:

	SinglePlayerScene(BaseGame*& scene, vector<BaseGame*>& sceneList) : currentScene(scene), scenes(sceneList){

	}
	

	PushdownResult OnUpdate(float dt, PushdownState** newState) override {
		unpauseTimer += dt;
		
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::F1)) {
			currentScene->setIsComplete(true);
			return PushdownResult::Pop;
		}

		if (unpauseTimer > delay){
			if (Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
				*newState = new PauseScreen(currentScene, scenes);
				return PushdownResult::Push;
			}
		}
		for (playerObject* p : currentScene->GetPlayerList()) {
			if (p->GetHasWon() == true) {
				*newState = new WinScreen(currentScene, scenes);
				return PushdownResult::Push;
			}
			if (p->GetScore() <= 0) {
				*newState = new LoseScreen(currentScene, scenes);
				return PushdownResult::Push;
			}
		}
		
		currentScene->GetRenderer()->DrawString("[ESC] TO PAUSE", Vector2(60, 10));

		return PushdownResult::NoChange;
	};
	void OnAwake() override {
		unpauseTimer = 0;
		currentScene = scenes.at(1);

		currentScene->Pause(false);
		if (currentScene->getIsComplete()) {
			currentScene->ResetScene();
		}

		Window::GetWindow()->ShowOSPointer(false);
	}

protected:
	float unpauseTimer = 0;
	float delay = 0.2f;

};


class MultiplayerScene : public PushdownState {
	BaseGame*& currentScene;
	vector<BaseGame*>& scenes;
public:

	MultiplayerScene(BaseGame*& scene, vector<BaseGame*>& sceneList) : currentScene(scene), scenes(sceneList) {

	}


	PushdownResult OnUpdate(float dt, PushdownState** newState) override {
		unpauseTimer += dt;

		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::F1)) {
			currentScene->setIsComplete(true);
			return PushdownResult::Pop;
		}

		if (unpauseTimer > delay) {
			if (Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
				*newState = new PauseScreen(currentScene, scenes);
				return PushdownResult::Push;
			}
		}
		for (playerObject* p : currentScene->GetPlayerList()) {
			if (p->GetHasWon() == true) {
				*newState = new WinScreen(currentScene, scenes);
				return PushdownResult::Push;
			}
			if (p->GetScore() <= 0) {
				*newState = new LoseScreen(currentScene, scenes);
				return PushdownResult::Push;
			}
		}


		Debug::Print("[ESC] TO PAUSE", Vector2(60, 10));

		return PushdownResult::NoChange;
	};
	void OnAwake() override {
		unpauseTimer = 0;
		std::cout << "In Multiplayer Game\n";
		currentScene = scenes.at(2);
		currentScene->Pause(false);
		if (currentScene->getIsComplete()) {
			currentScene->ResetScene();
		}
		Window::GetWindow()->ShowOSPointer(false);
	}

protected:
	float unpauseTimer = 0;
	float delay = 0.2f;

};

class TitleScreen : public PushdownState {
	BaseGame*& currentScene;
	vector<BaseGame*>& scenes;
public:


	TitleScreen(BaseGame*& scene, vector<BaseGame*>& sceneList) : currentScene(scene), scenes(sceneList) {
		
	}

	PushdownResult OnUpdate(float dt, PushdownState** newState) override {
		if (currentScene->GetSelectionObject()) {
			if (currentScene->GetSelectionObject()->GetName() == "singleButton") {
				currentScene->ResetSlectionObject();
				*newState = new SinglePlayerScene(currentScene, scenes);
				return PushdownResult::Push;
			}
		}

		if (currentScene->GetSelectionObject()) {
			if (currentScene->GetSelectionObject()->GetName() == "multiButton") {
				currentScene->ResetSlectionObject();
				*newState = new MultiplayerScene(currentScene, scenes);
				return PushdownResult::Push;
			}
		}

		if (currentScene->GetSelectionObject()) {
			if (currentScene->GetSelectionObject()->GetName() == "quitButton") {
				return PushdownResult::Pop;
			}
		}
		return PushdownResult::NoChange;
	}
	void OnAwake() override {
		std::cout << "Press Space to start or escape to Quit";
		currentScene = scenes.at(0);
		Window::GetWindow()->ShowOSPointer(true);
	}


};


#include "HomeScreen.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Common/TextureLoader.h"

#include "../CSC8503Common/PositionConstraint.h"

using namespace NCL;
using namespace CSC8503;

HomeScreen::HomeScreen() {
	InitScene();
}

void HomeScreen::InitScene() {
	InitWorld();
	InitCamera();

}

void HomeScreen::InitWorld() {
	world->ClearAndErase();
	physics->Clear();
	InitMenuBlocks();
	inSelectionMode = true;


}

void HomeScreen::DisplayText() {
	renderer->DrawString("Title Screen!", Vector2(40, 5), Vector3(0,0,0));
	renderer->DrawString("Single Player", Vector2(10, 50), Vector3(255, 0, 0));
	renderer->DrawString("Multiplayer", Vector2(40, 50), Vector3(255, 0, 0));
	renderer->DrawString("Quit", Vector2(75, 50), Vector3(255, 0, 0));

}

void HomeScreen::InitCamera() {

	world->GetMainCamera()->SetNearPlane(0.1f);
	world->GetMainCamera()->SetFarPlane(500.0f);
	world->GetMainCamera()->SetPitch(0.0f);
	world->GetMainCamera()->SetYaw(0.0f);
	world->GetMainCamera()->SetPosition(Vector3(50, 50, 50));
	lockedPlayer = nullptr;
}

void HomeScreen::UpdateGame(float dt) {

	DisplayText();


	UpdateKeys();
	SelectObject();
		
	physics->Update(dt);

	

	world->UpdateWorld(dt);
	renderer->Update(dt);

	Debug::FlushRenderables(dt);
	renderer->Render();
}

void HomeScreen::InitMenuBlocks() {
	GameObject* singlePlayerButton = AddCubeToWorld(Vector3(10, 50, -50), Vector3(10, 10, 10), -1.0f);
	singlePlayerButton->SetName("singleButton");

	GameObject* multiplayerButton = AddCubeToWorld(Vector3(50, 50, -50), Vector3(10, 10, 10), -1.0f);
	multiplayerButton->SetName("multiButton");

	GameObject* quitButton = AddCubeToWorld(Vector3(90, 50, -50), Vector3(10, 10, 10), -1.0f);
	quitButton->SetName("quitButton");
}
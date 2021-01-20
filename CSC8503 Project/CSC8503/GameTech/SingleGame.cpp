#include "SingleGame.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Common/TextureLoader.h"

#include "../CSC8503Common/PositionConstraint.h"

using namespace NCL;
using namespace CSC8503;

SingleGame::SingleGame() {
	InitWorld();
}


void SingleGame::InitWorld() {
	isComplete = false;
	paused = false;
	players.clear();

	world->ClearAndErase();
	physics->Clear();
	physics->UseGravity(true);
	
	Vector3 playerPos = Vector3(-30, 7, 150);
	InitLevelGeometry();
	InitPlayer(playerPos);
	

}

void SingleGame::DisplayText() {

	renderer->DrawString("F1 TO QUIT!", Vector2(5,5));
	
	string score  = std::to_string(lockedPlayer->GetScore());
	
	renderer->DrawString("Score: " + score, Vector2(5, 10));
}

playerObject* SingleGame::InitPlayer(Vector3 position) {
	float meshSize = 3.0f;
	float inverseMass = 0.6f;
	float elasticity = 0.3f;
	float friction = 1.1f;


	playerObject* player = new playerObject();
	AABBVolume* volume = new AABBVolume(Vector3(0.3f,0.85f, 0.3f)*meshSize);

	player->SetName("player");
	player->setHome(position);
	player->SetBoundingVolume((CollisionVolume*)volume);
	player->GetTransform().SetScale(Vector3(meshSize, meshSize, meshSize)).SetPosition(position);
	player->SetRenderObject(new RenderObject(&player->GetTransform(), charMeshA, nullptr, basicShader));
	player->GetRenderObject()->SetColour(Vector4(1, 0.6f, 1,0.5f));
	player->GetTransform().SetOrientation(Quaternion(0, -1, 0 ,1));
	
	player->SetPhysicsObject(new PhysicsObject(&player->GetTransform(), player->GetBoundingVolume()));
	player->GetPhysicsObject()->SetInverseMass(inverseMass);
	player->GetPhysicsObject()->SetElasticity(elasticity);
	player->GetPhysicsObject()->SetFriction(friction);
	player->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(player);

	lockedPlayer = player;
	players.push_back(player);

	return player;
}



void SingleGame::InitLevelGeometry() {
	//Sizes
	Vector3 deathSize(1500, 3,400);
	Vector3 goalSize(10, 2, 10);
	
	//Colours	
	Vector4 defaultColour(1,1,1,1.0f);
	Vector4 bounceColour(0, 0, 1, 0.5f);
	Vector4 slideColour(1,1,0,0.5f);
	Vector4 goalColour(1, 0, 1, 0.5f);

	//Ground Pieces
	AddGround(Vector3(0, 1, 150), Vector3(100, 2, 50), "ground", defaultColour);
	AddGround(Vector3(350, 1, 150), Vector3(50, 2, 50), "ground", defaultColour);
	AddGround(Vector3(756, 1, 150), Vector3(50, 2, 50), "ground", defaultColour);
	AddGround(Vector3(1100, 10, 150), Vector3(50, 2, 50), "ground", defaultColour);
	//Walls
	AddGround(Vector3(0, 6, 100), Vector3(100, 2, 3), "wall", defaultColour);
	AddGround(Vector3(0, 6, 200), Vector3(100, 2, 3), "wall", defaultColour);
	AddGround(Vector3(200, 6, 100), Vector3(1, 2, 3), "wall", defaultColour);
	AddGround(Vector3(200, 6, 200), Vector3(1, 2, 3), "wall", defaultColour);
	AddGround(Vector3(350, 6, 100), Vector3(50, 2, 3), "wall", defaultColour);
	AddGround(Vector3(350, 6, 200), Vector3(50, 2, 3), "wall", defaultColour);

	AddGround(Vector3(750, 6, 100), Vector3(50, 2, 3), "wall", defaultColour);
	AddGround(Vector3(750, 6, 200), Vector3(50, 2, 3), "wall", defaultColour);

	//Constraint Objects
	BridgeConstraintTest(Vector3(408.5f,1,150));
	
    //Misc Obstacles
	AddGround(Vector3(200.0f, 1, 150), Vector3(99, 2, 50), "slide", slideColour);
	AddGround(Vector3(875, -20 , 150),Vector3(20, 2, 20), "bounce", bounceColour);

	AddCubeWall(Vector3(20, 6, 130), 1, 10);
	AddBallPit(Vector3(750, 6, 130), 9, 8);
	//State Obstacles
	testStateObject = AddStateObjectToWorld(Vector3(200, 5, 150));


	//Goal
	AddGround(Vector3(1200, 10.5f, 150), Vector3(goalSize),"goal",goalColour);

	//Death Plane
	AddDeathBarrier(deathSize);
	//Bonuses
	AddBonusToWorld(Vector3(50, 7, 150));
	AddBonusToWorld(Vector3(60, 7, 150));
	AddBonusToWorld(Vector3(40, 7, 125));
	AddBonusToWorld(Vector3(40, 7, 175));
	AddBonusToWorld(Vector3(190, 7, 110));
	AddBonusToWorld(Vector3(210, 7, 190));
	AddBonusToWorld(Vector3(350, 7, 125));
	AddBonusToWorld(Vector3(350, 7, 175));
	AddBonusToWorld(Vector3(770, 7, 150));
	AddBonusToWorld(Vector3(1120, 17, 150));


}

GameObject* SingleGame::AddGround(Vector3 position, Vector3 size, string name, Vector4 colour) {
	GameObject* ground = new groundObject();
	AABBVolume* volume = new AABBVolume(size);
	ground->SetName(name);

	ground->SetBoundingVolume((CollisionVolume*)volume);
	ground->GetTransform().SetPosition(position).SetScale(size * 2);
	ground->SetRenderObject(new RenderObject(&ground->GetTransform(), cubeMesh, basicTex, basicShader));
	ground->GetRenderObject()->SetColour(colour);

	ground->SetPhysicsObject(new PhysicsObject(&ground->GetTransform(), ground->GetBoundingVolume()));
	ground->GetPhysicsObject()->SetInverseMass(0);
	ground->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(ground);
	return ground;
	
}



GameObject* SingleGame::AddDeathBarrier(Vector3 size) {
	GameObject* ground = new groundObject();
	AABBVolume* volume = new AABBVolume(size);
	ground->SetName("death");

	ground->SetBoundingVolume((CollisionVolume*)volume);
	ground->GetTransform().SetPosition(Vector3(-100,-50,150)).SetScale(size * 2);
	ground->SetRenderObject(new RenderObject(&ground->GetTransform(), cubeMesh, basicTex, basicShader));
	ground->GetRenderObject()->SetColour(Vector4(1, 0, 0, 0.5f));
	ground->SetPhysicsObject(new PhysicsObject(&ground->GetTransform(), ground->GetBoundingVolume()));
	ground->GetPhysicsObject()->SetInverseMass(0);
	ground->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(ground);
	return ground;

}

void SingleGame::AddCubeWall(Vector3 startPos, int width, int height) {
	Vector3 cubeSize(4, 4, 4);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			AddCubeToWorld(Vector3(startPos.x + (cubeSize.x * i) + 5, startPos.y  + 10, startPos.z + (cubeSize.z * j)) , cubeSize);
		}
	}
}

void SingleGame::AddBallPit(Vector3 startPos, int width, int height) {
	float sphereSize = 3;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			AddSphereToWorld(Vector3(startPos.x + (sphereSize * i) + 5, startPos.y + 10, startPos.z + (sphereSize * j)), sphereSize);
		}
	}
}
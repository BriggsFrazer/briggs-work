#include "MultiGame.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Common/TextureLoader.h"

#include "../CSC8503Common/PositionConstraint.h"

using namespace NCL;
using namespace CSC8503;

MultiGame::MultiGame() {
	testStateObject = NULL;

	InitWorld();
	physics->UseGravity(false);

}

void MultiGame::InitWorld() {
	isComplete = false;
	paused = false;
	players.clear();

	world->ClearAndErase();
	physics->Clear();
	physics->UseGravity(true);
	Vector3 playerPos = Vector3(50, 0, 50);
	Vector3 aiPos = Vector3(20, 0, 20);

	InitLevelGeometry();
	InitPlayer(playerPos);
	InitAI(aiPos);

}

void MultiGame::InitLevelGeometry() {
	InitFloor();
	InitWalls();
}

void MultiGame::InitWalls() {
	QuaterWalls();
}

void MultiGame::QuaterWalls() {
	Vector4 defaultColour(1, 1, 1, 1.0f);
	Vector3 squareSize = Vector3(gridSquare.x, 2, gridSquare.y);
	float height = 20;
	float width = 20;

	//Small Squares
	//AddGround(Vector3(gridSquare.x * 4, 10, gridSquare.y * 4), squareSize, "wall", defaultColour);
	//AddGround(Vector3(gridSquare.x * 4, 10, gridSquare.y * 19), squareSize, "wall", defaultColour);
	//AddGround(Vector3(gridSquare.x * 19, 10, gridSquare.y * 4), squareSize, "wall", defaultColour);
	//AddGround(Vector3(gridSquare.x * 19, 10, gridSquare.y * 19), squareSize, "wall", defaultColour);

	//L Shapes



	//Outer Walls
	AddGround(Vector3(width * gridSquare.x, 2, -gridSquare.x), Vector3(squareSize.x * height, 2 , squareSize.z), "wall", defaultColour);
	AddGround(Vector3(width * gridSquare.x, 2, 2 * width * gridSquare.x + gridSquare.x), Vector3(squareSize.x * height, 2, squareSize.z), "wall", defaultColour);
	AddGround(Vector3(-gridSquare.y, 2, gridSquare.y * height), Vector3(squareSize.x , 2, squareSize.z * width), "wall", defaultColour);
	AddGround(Vector3(2 * height * gridSquare.y + gridSquare.y, 2, gridSquare.y * height), Vector3(squareSize.x, 2, squareSize.z * width), "wall", defaultColour);


}

void MultiGame::InitFloor() {
	//Putting 20x20 grid of floor pieces
	float height = 20;
	float width = 20;
	Vector4 defaultColour(1, 1, 1, 1.0f);
	AddGround(Vector3(width * gridSquare.x, -3, height*gridSquare.y), Vector3(gridSquare.x*height, 2, gridSquare.y*width), "ground", defaultColour);


}
void MultiGame::InitSticky() {

}

aiPlayerObject* MultiGame::InitAI(Vector3 position) {
	float meshSize = 3.0f;
	float inverseMass = 0.6f;
	float elasticity = 0.3f;
	float friction = 1.1f;


	aiPlayerObject* player = new aiPlayerObject(lockedPlayer);
	AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.85f, 0.3f) * meshSize);

	player->SetName("enemy");
	player->setHome(position);
	player->SetBoundingVolume((CollisionVolume*)volume);
	player->GetTransform().SetScale(Vector3(meshSize, meshSize, meshSize)).SetPosition(position);
	player->SetRenderObject(new RenderObject(&player->GetTransform(), charMeshA, nullptr, basicShader));
	player->GetRenderObject()->SetColour(Vector4(0.6f, 1, 1, 0.5f));
	player->GetTransform().SetOrientation(Quaternion(0, -1, 0, 1));

	player->SetPhysicsObject(new PhysicsObject(&player->GetTransform(), player->GetBoundingVolume()));
	player->GetPhysicsObject()->SetInverseMass(inverseMass);
	player->GetPhysicsObject()->SetElasticity(elasticity);
	player->GetPhysicsObject()->SetFriction(friction);
	player->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(player);

	enemyAI = player;

	players.push_back(player);

	return player;
}
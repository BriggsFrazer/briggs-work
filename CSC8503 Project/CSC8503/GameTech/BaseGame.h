#pragma once
#include "GameTechRenderer.h"
#include "../CSC8503Common/PhysicsSystem.h"
#include"../GameTech/StateGameObject.h"

namespace NCL {
	namespace CSC8503 {
		class BaseGame {
		public:
			BaseGame();
			~BaseGame();

			virtual void UpdateGame(float dt);

			GameObject* GetSelectionObject() { return selectionObject; };
			void ResetSlectionObject() { 
				selectionObject->GetRenderObject()->SetColour(Vector4(1, 1, 1, 0.5f));
				selectionObject = nullptr; 
			};

			vector<playerObject*> BaseGame::GetPlayerList(){return players;}

			bool getIsComplete() { return isComplete; };
			void setIsComplete(bool complete) { isComplete = complete; };

			void ResetScene() { InitWorld(); };
			void Pause(bool state) { paused = state; };

			GameTechRenderer* GetRenderer() {
				return renderer;
			}

		protected:
			virtual void InitialiseAssets();

			virtual void InitCamera();
			void UpdateKeys();

			virtual void InitWorld();

			void InitGameExamples();

			void InitSphereGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, float radius);
			void InitMixedGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing);
			void InitCubeGridWorld(int numRows, int numCols, float rowSpacing, float colSpacing, const Vector3& cubeDims);
			void InitDefaultFloor();
			void BridgeConstraintTest(Vector3 startPos);

			bool SelectObject();
			void MoveSelectedObject();
			virtual void DisplayText();
			void DebugObjectMovement();
			void LockedObjectMovement();

			

			GameObject* AddFloorToWorld(const Vector3& position);
			GameObject* AddSphereToWorld(const Vector3& position, float radius, float inverseMass = 10.0f);
			GameObject* AddCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass = 10.0f);

			GameObject* AddCapsuleToWorld(const Vector3& position, float halfHeight, float radius, float inverseMass = 10.0f);

			GameObject* AddPlayerToWorld(const Vector3& position);
			GameObject* AddEnemyToWorld(const Vector3& position);
			bonusObject* AddBonusToWorld(const Vector3& position);

			

			GameTechRenderer* renderer;
			PhysicsSystem* physics;
			GameWorld* world;

			bool useGravity;
			bool inSelectionMode;

			float		forceMagnitude;

			GameObject* selectionObject = nullptr;

			OGLMesh* capsuleMesh = nullptr;
			OGLMesh* cubeMesh = nullptr;
			OGLMesh* sphereMesh = nullptr;
			OGLTexture* basicTex = nullptr;
			OGLShader* basicShader = nullptr;

			//Coursework Meshes
			OGLMesh* charMeshA = nullptr;
			OGLMesh* charMeshB = nullptr;
			OGLMesh* enemyMesh = nullptr;
			OGLMesh* bonusMesh = nullptr;

			//Coursework Additional functionality	
			playerObject* lockedPlayer;
			vector<playerObject*> players;

			aiPlayerObject* enemyAI;

			Vector3 lockedOffset = Vector3(0 , 7, 0);
			void LockCameraToPlayer(playerObject* o) {
				lockedPlayer = o;
			}

			//AI State Objects
			StateGameObject* AddStateObjectToWorld(const Vector3& position);
			StateGameObject* testStateObject = NULL;

			bool isComplete = false;

			bool paused = false;
		};
	}
}


#pragma once
#include "GameObject.h"
#include "../CSC8503Common/NavigationGrid.h"

#include "../CSC8503Common/BehaviourAction.h"
#include "../CSC8503Common/BehaviourSequence.h"
#include "../CSC8503Common/BehaviourSelector.h"

namespace NCL {
	namespace CSC8503 {

		//Player
		class playerObject : public GameObject {
		public:
			playerObject() {};
			~playerObject() {};

			void OnCollisionBegin(GameObject* otherObject) {
				if (otherObject->GetName() == "ground" || otherObject->GetName() == "obstacle" ) {
					float topGroundY = otherObject->GetTransform().GetPosition().y + otherObject->GetTransform().GetScale().y;
					if (this->GetTransform().GetPosition().y > topGroundY) {
						numJumps = 1;
					}
				}
				if (otherObject->GetName() == "bonus") {
					score += 25;
					coins += 1;
					this->setHome(otherObject->GetTransform().GetPosition());
				}
				if (otherObject->GetName() == "goal") {
					hasWon = true;
				}
				if (otherObject->GetName() == "death") {
					this->GetTransform().SetPosition(home);


					this->GetPhysicsObject()->SetAngularVelocity(Vector3(0,0,0));
					this->GetPhysicsObject()->SetLinearVelocity(Vector3(0, 0, 0));

				}

				if (otherObject->GetName() == "bounce") {
					Vector3 vel = this->GetPhysicsObject()->GetLinearVelocity();

					this->GetPhysicsObject()->AddForce(Vector3(0, 3000*vel.y, 0));

				}

				if (otherObject->GetName() == "slide") {
					this->GetPhysicsObject()->SetFriction(0.6f);
				}

				if (otherObject->GetName() == "obstacle") {
					numJumps = 1;
				}

			}

			void OnCollisionEnd(GameObject* otherObject) {
				if (otherObject->GetName() == "ground") {
					numJumps = 0;
				}
				if (otherObject->GetName() == "obstacle") {
					float topGroundY = otherObject->GetTransform().GetPosition().y + otherObject->GetTransform().GetScale().y;
					if (this->GetTransform().GetPosition().y > topGroundY) {
						numJumps = 1;
					}
				}
				if (otherObject->GetName() == "slide") {
					this->GetPhysicsObject()->SetFriction(1.1f);
				}

			}

			void UpdateScore(float dt) {
				currScoreTime -= dt;
				if (currScoreTime <= 0) {
					score -= scoreDrop;
					currScoreTime += scoreTimer;
				}
				
			}

			int GetJumps() {
				return numJumps;
			}

			void RemoveJump() {
				numJumps -= 1;
			}

			int GetScore() {
				return score;
			}

			int GetHasWon() {
				return hasWon;
			}

			void setHome(Vector3 newHome) {
				home = newHome;
			}

			Vector3 getHome() {
				return home;
			}

			int GetCoins() {
				return coins;
			}
		protected:

			int score = 1000;
			int scoreDrop = 10;
			float scoreTimer = 1;
			float currScoreTime = 1;
			int numJumps = 1;
			bool hasWon = false;
			int coins = 0;
			Vector3 home = Vector3(0,0,0);

		};

		class aiPlayerObject : public playerObject {
		public:
			aiPlayerObject(playerObject* curPlayer) {
				mainPlayer = curPlayer;
			}

			void UpdateAI(float dt) {

				if (stuckTime >= stuckTimer) {
					this->GetTransform().SetPosition(mainPlayer->GetTransform().GetPosition() + Vector3(0, 10, 0));
					stuckTime = 0;
					AIChosen = false;
				}

				if (AIChosen == false) {
					AIChosen = true;
					BehaviourTree();
					GeneratePath(targetLocation);
					if (testNodes.size() == 0) {
						AIChosen = false;
					}

				}

				if (testNodes.size() > 0) {
					UpdateCurrentNode(dt);
					MoveToNextNode();
				}
				DisplayPath();

			}


			void BehaviourTree() {



				BehaviourAction* chooseRandDest = new BehaviourAction("Choose Random Destination", [&](float dt, BehaviourState state)->BehaviourState {
					if (state == Initialise) {
						std::cout << "Choosing random location \n";
						ChooseNewTarget();
						return Success;
					}

					return state;
					}
				);

				BehaviourAction* findGoal = new BehaviourAction("Find Goal", [&](float dt, BehaviourState state)->BehaviourState {
					if (state == Initialise) {
						std::cout << "Checking for goal \n";
						//CHECK FOR GOAL ON MAP
						//IF GOAL, UPDATE TARGET TO GOAL
						//RETURN SUCCESS
						//IF NO GOAL, RETURN FAIL
						return Success;
					}
					return state;
					}
				);



				BehaviourAction* findCoin = new BehaviourAction("Find Coin", [&](float dt, BehaviourState state) -> BehaviourState {
					if (state == Initialise) {
						std::cout << "Checking for coin \n";
						//CHECK FOR GOAL ON MAP
						//IF GOAL, UPDATE TARGET TO GOAL
						//RETURN SUCCESS
						//IF NO GOAL, RETURN FAIL
						return Success;
					}

					return state;
					}
				);
				



				BehaviourSequence* wanderSeq = new BehaviourSequence("Wander Sequence");
				wanderSeq->AddChild(chooseRandDest);


				BehaviourSelector* destSelect = new BehaviourSelector("Destination Selector");
				destSelect->AddChild(findGoal);
				destSelect->AddChild(findCoin);

				BehaviourSequence* rootSequence = new BehaviourSequence("Root Sequence");
				rootSequence->AddChild(wanderSeq);
				rootSequence->AddChild(destSelect);

				rootSequence->Reset();

				BehaviourState state = Ongoing;
				std::cout << "Choosing Destination! \n";
				while (state == Ongoing) {
					state = rootSequence->Execute(1.0f);

				}
				if (state == Success) {
					std::cout << "Found A Destination! \n";
				}

			}


			void GeneratePath(Vector3 endPos) {
				NavigationGrid grid("multiPlayerGrid.txt");
				NavigationPath outPath;

				Vector3 startPos = this->GetTransform().GetPosition();


				bool found = grid.FindPath(startPos, endPos, outPath);

				Vector3 pos;
				while (outPath.PopWaypoint(pos)) {
					testNodes.push_back(pos);
				}
			}


			void MoveToNextNode() {
				Vector3 dirToNext = testNodes[currentNode] - this->GetTransform().GetPosition();
				dirToNext.Normalise();
				this->GetPhysicsObject()->AddForce(Vector3(50,0,50) * dirToNext);
				
			}

			void UpdateCurrentNode(float dt) {
				//If touching next node move on to the next
				stuckTime += dt;
				if (((testNodes[currentNode] - this->GetTransform().GetPosition()).Length() < 10) )  {
					if (testNodes[currentNode] != testNodes[testNodes.size() - 1]) {
						currentNode += 1;
						stuckTime = 0;
						std::cout << "at new node \n";
						std::cout << testNodes[testNodes.size() - 1]  << "\n";
					}
					else {
						std::cout << "reached the end! \n";
						testNodes.clear();
						currentNode = 1;
						stuckTime = 0;
						AIChosen = false;
					}
				}
			}

			void ChooseNewTarget() {
				targetLocation = Vector3(rand() % 360 + 20, 0, rand() % 360 + 20);
			}

			void DisplayPath() {
				for (int i = 1; i < testNodes.size(); ++i) {

					Vector3 a = testNodes[i - 1];
					Vector3 b = testNodes[i];

					Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
				}
			}



		protected:
			playerObject* mainPlayer;
			float stuckTimer = 10.0f;
			float stuckTime = 0.0f;
			vector<Vector3> testNodes;
			Vector3 targetLocation = Vector3(0,0,0);
			int currentNode;
			bool AIChosen = false;

		};

		class environmentObject : public GameObject {

		};

		class groundObject : public environmentObject {

		};

		class bonusObject : public GameObject {

			void OnCollisionBegin(GameObject* otherObject) {
				if (otherObject->GetName() == "player" || otherObject->GetName() == "enemy") {
					isActive = false;
				}

			}
		};


		

	}
}
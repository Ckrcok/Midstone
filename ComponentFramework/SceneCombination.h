#ifndef SCENE_COMBINATION_H
#define SCENE_COMBINATION_H

// Basic include
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "CameraActorFPS.h"
#include "Skybox.h"

// Extra include
#include "EnemyActor.h"
#include "PlayerGun.h"
#include "Collision.h"
#include "Wall.h"
#include "Graph.h"
#include "NodeTile.h"

// Namespaces
using namespace MATH;
using namespace std;

// Forward declarations 
union SDL_Event;
class Actor;
class Shader;

class SceneCombination : public Scene
{
private:
	// Camera
	CameraActorFPS* cameraFPS;

	// Empty enemy
	EnemyActor* emptyActor;

	// Shader
	Shader* shader;

	// Graph
	Graph* graph;
	vector<vector<NodeTile*>> tiles;
	vector<Node*> nodes;

	int gridWidth = 30;
	int gridHeight = 15;
	int tileWidth = 4;
	int tileHeight = 4;

	// Render variables
	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];

	PlayerGun* playerGun;				// Gun of the player
	vector<Wall*> theWalls;				// List of walls
	vector<EnemyActor*> enemiesInRooms;	// List of enemies
	vector<Box*> roomTriggers;			// List of room triggers

	// Booleans
	bool hasWeapon = false;
	bool hasHealth = false;
	bool hasKey = false;

	// Variables for collisions
	Vec3 rotationVec = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 test = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 resultPlayer = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerPlayer = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerPlayer = Vec3(0.0f, 0.0f, 0.0f);

	Vec3 resultB = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerB = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerB = Vec3(0.0f, 0.0f, 0.0f);

	// Collider boxes
	Box* playerColliderBox = new Box(test, minCornerPlayer, maxCornerPlayer, emptyActor);
	Box* blueBox = new Box(test, minCornerB, maxCornerB, emptyActor);

	// Enemies
	EnemyActor* enemyA = new EnemyActor(Vec3(-17.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyB = new EnemyActor(Vec3(-2.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyC = new EnemyActor(Vec3(8.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyD = new EnemyActor(Vec3(10.0f, 0.0f, -6.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyE = new EnemyActor(Vec3(15.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyF = new EnemyActor(Vec3(16.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);

	// Collision values for enemies
	Vec3 minValueTriggerA = (Vec3(-17.0f, 0.0f, -24.0f) - (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerB = (Vec3(-2.0f, 0.0f, -24.0f) - (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerC = (Vec3(8.0f, 0.0f, -20.0f) - (Vec3(16.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerD = (Vec3(10.0f, 0.0f, -6.0f) - (Vec3(2.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerE = (Vec3(15.0f, 0.0f, 16.0f) - (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerF = (Vec3(16.0f, 0.0f, -4.0f) - (Vec3(4.0f, 1.0f, 10.0f)));
	Vec3 maxValueTriggerA = (Vec3(-17.0f, 0.0f, -24.0f) + (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerB = (Vec3(-2.0f, 0.0f, -24.0f) + (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerC = (Vec3(8.0f, 0.0f, -20.0f) + (Vec3(16.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerD = (Vec3(10.0f, 0.0f, -6.0f) + (Vec3(2.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerE = (Vec3(15.0f, 0.0f, 16.0f) + (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerF = (Vec3(16.0f, 0.0f, -4.0f) + (Vec3(4.0f, 1.0f, 10.0f)));

	// Box collisions
	Box* triggerRoomA = new Box(Vec3(-17.0f, 0.0f, -24.0f), minValueTriggerA, maxValueTriggerA, enemyA);	//= Box(minCornerB, maxCornerB);
	Box* triggerRoomB = new Box(Vec3(-2.0f, 0.0f, -24.0f), minValueTriggerB, maxValueTriggerB, enemyB);		//= Box(minCornerB, maxCornerB);
	Box* triggerRoomC = new Box(Vec3(8.0f, 0.0f, -20.0f), minValueTriggerC, maxValueTriggerC, enemyC);		//= Box(minCornerB, maxCornerB);
	Box* triggerRoomD = new Box(Vec3(10.0f, 0.0f, -6.0f), minValueTriggerD, maxValueTriggerD, enemyD);		//= Box(minCornerB, maxCornerB);
	Box* triggerRoomE = new Box(Vec3(15.0f, 0.0f, 16.0f), minValueTriggerE, maxValueTriggerE, enemyE);		//= Box(minCornerB, maxCornerB);
	Box* triggerRoomF = new Box(Vec3(16.0f, 0.0f, -4.0f), minValueTriggerF, maxValueTriggerF, enemyF);		//= Box(minCornerB, maxCornerB);

	// Functions
	void CreateNodeLayout();
	void CalculateConnectionWeights();

public:
	// Scene creation and destroy functions
	explicit SceneCombination();
	virtual ~SceneCombination();

	// Scene basic functions
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Render() const override;
	virtual void Update(const float deltaTime) override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif // SCENE_COMBINATION_H

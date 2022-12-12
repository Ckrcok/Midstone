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
	//CameraActor* camera;
	CameraActorFPS* cameraFPS;
	EnemyActor* emptyActor;

	// Scene actors
	Actor* ground;
	Actor* ceiling;
	Actor* light;
	Actor* lightSource0;
	Actor* lightSource1;
	Actor* lightSource2;
	Actor* lightSource3;
	Actor* lightSource4;
	Actor* lightSource5;
	Actor* lightSource6;
	Actor* lightSource7;
	Actor* lightSource8;

	// Shader
	Shader* shader;

	// Render variables
	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];

	// Gun of the player
	PlayerGun* playerGun;
	vector<Wall*> theWalls;
	vector<EnemyActor*> enemiesInRooms;
	vector<Box*> roomTriggers;

	bool hasWeapon = false;
	bool hasHealth = false;
	bool hasKey = false;
	bool gameOver = false;
	bool gameLost = false;
	bool gameWon = false;
	float playerHealth = 1000;
	Vec3 rotationVec = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 test = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 resultPlayer = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerPlayer = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerPlayer = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 minCornerEnemy = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerEnemy = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 enemyPos;
	Vec3 resultB = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerB = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerB = Vec3(0.0f, 0.0f, 0.0f);

	Box* playerColliderBox = new Box(test, minCornerPlayer, maxCornerPlayer, emptyActor); //= Box(minCornerA, maxCornerA);
	Box* enemyColliderBox = new Box(test, minCornerEnemy, maxCornerEnemy, emptyActor); //= Box(minCornerA, maxCornerA);

	Box* blueBox = new Box(test, minCornerB, maxCornerB, emptyActor);//= Box(minCornerB, maxCornerB);




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
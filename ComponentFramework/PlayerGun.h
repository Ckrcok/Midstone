#ifndef PLAYER_GUN_H
#define	PLAYER_GUN_H

// Basic include
#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"

// Extra include
#include "CameraActor.h"
#include "CameraActorFPS.h"
#include "Bullet.h"

// Namespaces
using namespace MATH;
using namespace std;

// Using class Bullet for a special include (fixed bugs)
class Bullet;

class PlayerGun : public Actor
{
private:
	// Position & Rotation
	Vec3 position;
	float rotation;
	Vec3 rotationAxis;
	Vec3 offset;

	// Model
	Actor* model_3D;
	Shader* shader;

	Matrix4 gunMatrix;

	// Player
	CameraActorFPS* cameraFPS;

public:
	// Constructors
	PlayerGun(Vec3 offset_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActorFPS* camera_, Component* parent_);
	PlayerGun();
	~PlayerGun();

	// Bullets
	vector<Bullet*> spawnedBullets;
	int bulletLabel = 0;

	// Basic functions
	bool OnCreate();
	void OnDestroy();
	void Render();
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& sdlEvent);

	// Extra bullets
	void SpawnBullet(Vec3 velocity_);
	void HandleDestroyBullet();

	// Get functions
	inline Matrix4 GetGunMatrix() { return gunMatrix; }
};

#endif // !PLAYER_GUN_H

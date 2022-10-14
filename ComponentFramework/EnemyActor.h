#ifndef ENEMY_ACTOR_H
#define ENEMY_ACTOR_H

#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"
#include "CameraActor.h"

using namespace MATH;
using namespace std;

class  EnemyActor : public Actor
{
private:
	// Position & Rotation
	Vec3 position;
	float rotation;
	Vec3 rotationAxis;

	// Model
	Actor* model_3D;
	Shader* shader;

	// Movement target
	vector<Vec3> targets;
	int currentTarget;

	// Player
	Vec3 playerPos;

	void MoveToTarget(float deltaTime);
	float GetDistance(Vec3 p, Vec3 q);

	void Attack();

public:
	EnemyActor(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, Component* parent_);
	~EnemyActor();

	bool OnCreate();
	void OnDestroy();
	void Render();
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& sdlEvent);
};

#endif

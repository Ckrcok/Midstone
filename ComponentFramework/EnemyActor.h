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
	float timeBetweenTargets = 2.0f;
	float currentTimeBetweenTargets;

	// Player
	Actor* player;

	// Stun variables
	bool isStunned = false;
	float currentStunTimer;

	void MoveToTarget(float deltaTime);
	void FaceTarget(float deltaTime);

	float GetDistance(Vec3 p, Vec3 q);

	Actor* attackTarget = nullptr;
	void Attack(float deltaTime);
	float attackInterval;
	float currentAttackValue;

public:
	EnemyActor(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, Actor* player_, Component* parent_);
	~EnemyActor();

	bool OnCreate();
	void OnDestroy();
	void Render();
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& sdlEvent);

	void AttackTarget(Actor* target_, float attackInterval_)
	{
		attackTarget = target_;
		attackInterval = attackInterval_;
	};

	void StunEnemy(float stunTime_)
	{
		currentStunTimer = stunTime_;
		isStunned = true;
	};

	void SetPlayer(Actor* player_)
	{
		player = player_;
	}
};

#endif

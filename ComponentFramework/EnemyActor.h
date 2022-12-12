#ifndef ENEMY_ACTOR_H
#define ENEMY_ACTOR_H

// Basic include
#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"

// Extra include
#include "CameraActorFPS.h"

// Namespaces
using namespace MATH;
using namespace std;

class  EnemyActor : public Actor
{
private:
	// Position & Rotation
	Vec3 position;
	float rotation;
	Vec3 rotationAxis;

	// Model & Shader
	Actor* model_3D;
	Shader* shader;

	// Movement target
	vector<Vec3> targets;
	int currentTarget;
	float timeBetweenTargets = 2.0f;
	float currentTimeBetweenTargets;

	// Player
	CameraActorFPS* camera;

	// Stun variables
	bool isStunned = false;
	float currentStunTimer;

	float GetDistance(Vec3 p, Vec3 q);

	Actor* attackTarget = nullptr;
	void Attack(float deltaTime);
	float attackInterval;
	float currentAttackValue;

public:
	void MoveToTarget(float deltaTime);
	void MoveToTarget(Vec3 playerPos);

	// Constructors
	EnemyActor(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActorFPS* player_, Component* parent_);
	~EnemyActor();

	// Basic functions
	bool OnCreate();
	void OnDestroy();
	void Render();
	void Update(float deltaTime);
	void HandleEvents(const SDL_Event& sdlEvent);

	// Variables
	Vec3 originalPos = position;
	float enemyHealth = 15.0f;
	float enemyDamage = 10.0f;

	// Attack
	void AttackTarget(Actor* target_, float attackInterval_)
	{
		attackTarget = target_;
		attackInterval = attackInterval_;
	};

	// Stun
	void StunEnemy(float stunTime_)
	{
		currentStunTimer = stunTime_;
		isStunned = true;
	};

	// Get function
	Vec3 getPositionEnemy()
	{
		// Because safak made me do the right thing
		return position;
	}

	// Set functions
	void SetCamera(CameraActorFPS* camera_)
	{
		cout << "New camera set! || Old camera: " << camera << " || New camera: " << camera_ << endl;

		camera = nullptr;
		camera = camera_;
	}

	void setPositionEnemy(Vec3 newPos_)
	{
		// Because safak made me do the right thing x2
		position = newPos_;
	}
	Vec3 getPos() { return position; }
	void setPos(Vec3 position_) { position = position_; }

};

#endif // !ENEMY_ACTOR_H

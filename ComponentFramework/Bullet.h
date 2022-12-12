#ifndef BULLET_H
#define BULLET_H

// Basic include
#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"
#include "PlayerGun.h"

// Namespaces
using namespace std;

// Using class PlayerGun for a special include (fixed bugs)
class PlayerGun;

class Bullet : public Actor
{
private:
	// Position & Velocity
	Vec3 position;
	Vec3 velocity;

	// Model
	Actor* model_3D;
	Shader* shader;
	PlayerGun* playerGun;

	// Timer variables
	float destroyAfterSeconds = 0.60f;
	float timer = 0.0f;

	// Label to recognize bullets
	int label;

	// Boolean to check if the bullet should be destroyed 
	bool bulletDestroyIsCalled = false;

public:
	Bullet(int label, Vec3 spawnPos, Vec3 velocity_, PlayerGun* playerGun_, Component* parent_);
	~Bullet();

	// Basic functions
	bool OnCreate();
	void Update(float deltaTime);
	void Render();
	void OnDestroy();

	// Get functions
	int GetLabel() { return label; };
	bool GetBulletDestroyIsCalled() { return bulletDestroyIsCalled; };
};

#endif // !BULLET_H

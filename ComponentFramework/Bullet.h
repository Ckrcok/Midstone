#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"

using namespace std;

class PlayerGun;

class Bullet : public Actor
{
private:
	Vec3 position;
	Vec3 velocity;

	// Model
	Actor* model_3D;
	Shader* shader;

	float destroyAfterSeconds = 5.0f;
	float timer = 0.0f;
	int label;

	bool bulletDestroyIsCalled = false;

public:
	Bullet(int label, Vec3 spawnPos, Vec3 velocity_, Component* parent_);
	~Bullet();

	bool OnCreate();
	void Update(float deltaTime);
	void Render();
	void OnDestroy();

	void OnCollision();
	int GetLabel() { return label; };
	bool GetBulletDestroyIsCalled() { return bulletDestroyIsCalled; };
};

#endif // !BULLET_H

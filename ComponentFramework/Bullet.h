#ifndef BULLET_H
#define BULLET_H

#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"
#include "CameraActor.h"

class Bullet : public Actor
{
private:
	Vec3 position;
	Vec3 velocity;

	// Model
	Actor* model_3D;
	Shader* shader;

public:
	Bullet(Vec3 spawnPos, Vec3 velocity_, Component* parent_);
	~Bullet();

	bool OnCreate();
	void Update(float deltaTime);
	void Render();
	void OnDestroy();
	void OnCollision();
};

#endif // !BULLET_H

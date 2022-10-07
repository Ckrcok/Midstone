#ifndef  ENEMY_H
#define ENEMY_H

#include "Vector.h"

class Enemy {
private:
	Vec3 position;
	float rotation;

public:
	Enemy(Vec3 spawnPosition, float spawnRotation);
	~Enemy();

	bool OnCreate();
	void Render();
	void Update(float deltaTime_);
};

#endif // ! ENEMY_H

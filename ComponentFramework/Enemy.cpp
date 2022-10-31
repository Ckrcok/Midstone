#include "Enemy.h"

Enemy::Enemy(Vec3 spawnPosition, float spawnRotation)
{
	position = spawnPosition;
	rotation = spawnRotation;
}

Enemy::~Enemy() {}

bool Enemy::OnCreate()
{
	return true;
}

void Enemy::Render()
{

}

void Enemy::Update(float deltaTime_)
{

}

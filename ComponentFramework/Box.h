#pragma once

// Basic include
#include <SDL.h>

#include "Actor.h"
#include "Trackball.h"
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"

// Extra include
#include "EnemyActor.h"

// Namespace
using namespace MATH;

class Box
{
public:
	// Coordinates
	Vec3 pos;
	Vec3 maxCoords;
	Vec3 minCoords;

	// Enemy variables
	EnemyActor* enemyRoom;
	float radius = 1.0f;

	// Constructor with no input variables (sets itself)
	Box()
	{
		pos = Vec3(0.0f, 0.0f, 0.0f);
		minCoords = Vec3(0.0f, 0.0f, 0.0f);
		maxCoords = Vec3(0.0f, 0.0f, 0.0f);
	}

	// Constructor with input variables
	Box(Vec3 pos_, Vec3 minCoords_, Vec3 maxCoords_, EnemyActor* enemyRoom_)
	{
		pos = pos_;
		minCoords = minCoords_;
		maxCoords = maxCoords_;

		enemyRoom = enemyRoom_;
	}

	// Update the positions
	void updateVertPos(Vec3 pos_, Vec3 minCoords_, Vec3 maxCoords_)
	{
		pos = pos_;
		minCoords = minCoords_;
		maxCoords = maxCoords_;
	}
};

#pragma once
#include "Actor.h"
#include "Trackball.h"
#include <SDL.h>
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"

using namespace MATH;

class Box 
{
public:
	Vec3 maxCoords;
	Vec3 minCoords;
	Vec3 pos;

	float radius = 1.0f;
	//Constructors
	Box(){ 
		minCoords = Vec3(0.0f,0.0f,0.0f); 
		maxCoords = Vec3(0.0f, 0.0f, 0.0f);
		pos = Vec3(0.0f, 0.0f, 0.0f);
	}

	Box(Vec3 pos_, Vec3 minCoords_, Vec3 maxCoords_){ 
	pos = pos_;
	minCoords = minCoords_; 
	maxCoords = maxCoords_;
	}
	void updateVertPos(Vec3 pos_, Vec3 minCoords_, Vec3 maxCoords_) { pos = pos_; minCoords = minCoords_; maxCoords = maxCoords_; }

};
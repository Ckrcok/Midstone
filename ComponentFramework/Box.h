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

	//Constructors
	Box(){ 
		minCoords = Vec3(0.0f,0.0f,0.0f); 
		maxCoords = Vec3(0.0f, 0.0f, 0.0f);}

	Box(Vec3 minCoords_, Vec3 maxCoords_) 
	{ minCoords = minCoords_; 
	maxCoords = maxCoords_;}
	void updateVertPos(Vec3 minCoords_, Vec3 maxCoords_) { minCoords = minCoords_; maxCoords = maxCoords_; }

};
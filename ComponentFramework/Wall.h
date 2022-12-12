#ifndef WALL_H
#define WALL_H

#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"
#include "CameraActorFPS.h"
#include "Vector.h"

using namespace MATH;
using namespace std;

class  Wall : public Actor
{
public:
	// Position & Rotation
	Vec3 position;
	float rotation;
	Vec3 rotationAxis;

	// ID & Radius
	char id;
	float radius = 2.5f;

	// Model
	Actor* objFile;
	Shader* objShader;

public:
	// Constructorsd
	Wall(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActorFPS* player_, Component* parent_, char id);
	Wall(float radius_, Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActorFPS* player_, Component* parent_, char id);
	~Wall();

	// Basic functions
	bool OnCreate();
	void OnDestroy();
	void Render();

	// Extra functions
	void moveWall(float toatlTime_, Wall* theObject_);
	void rotateWall(float toatlTime_);
	void positionInstructions();

	// Get function
	Vec3 getPos() { return position; }
};

#endif	//!WALL_H

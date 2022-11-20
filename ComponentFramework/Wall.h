#ifndef WALL_H
#define WALL_H

#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"
#include "CameraActor.h"
#include "Vector.h"

using namespace MATH;
using namespace std;

class  Wall : public Actor
{
public:
	Vec3 position;
	float rotation;
	Vec3 rotationAxis;
	char id;
	float radius = 2.5f;
	//vector<std::variant<Vec3,float, Vec3, CameraActor, Component>> northWalls;
	// Model
	Actor* objFile;
	Shader* shader;
public:
	Wall(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* player_, Component* parent_, char id);
	Wall(float radius_, Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* player_, Component* parent_, char id);
	~Wall();

	bool OnCreate();
	void OnDestroy();
	void Render();
	void moveWall();

	Vec3 getPos() { return position; }
	
};

#endif

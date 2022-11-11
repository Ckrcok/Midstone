#ifndef WALL_H
#define WALL_H

#include <SDL.h>

#include "Actor.h"
#include "Shader.h"
#include "Scene.h"
#include "Debug.h"
#include "MMAth.h"
#include "CameraActor.h"

using namespace MATH;
using namespace std;

class  Wall : public Actor
{
public:
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
	Vec3 position;
	float rotation;
	Vec3 rotationAxis;

	// Model
	Actor* objFile;
	Shader* shader;
public:
	Wall(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* player_, Component* parent_);
	~Wall();

	bool OnCreate();
	void OnDestroy();
	void Render();

	
};

#endif

#ifndef SCENE_COMBINATION_H
#define SCENE_COMBINATION_H

// Basic include
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "Skybox.h"

// Extra include
#include "EnemyActor.h"
#include "PlayerGun.h"

// Namespaces
using namespace MATH;
using namespace std;

// Forward declarations 
union SDL_Event;
class Actor;
class Shader;

class SceneCombination : public Scene
{
private:
	// Camera
	CameraActor* camera;

	// Shader
	Shader* shader;

	// Render variables
	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];

	// Gun of the player
	PlayerGun* playerGun;

	// List of enemies
	vector<EnemyActor*> enemies;

public:
	// Scene creation and destroy functions
	explicit SceneCombination();
	virtual ~SceneCombination();

	// Scene basic functions
	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Render() const override;
	virtual void Update(const float deltaTime) override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif // SCENE_COMBINATION_H

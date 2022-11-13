#ifndef SCENE3_H
#define SCENE3_H

#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "Skybox.h"
#include "EnemyActor.h"
#include "PlayerGun.h"

using namespace MATH;
using namespace std;

// Forward declarations 
union SDL_Event;
class Actor;
class Shader;

class Scene3 : public Scene
{
private:
	vector<EnemyActor*> enemies;

	Shader* shader;

	Trackball* trackball;
	CameraActor* camera;
	PlayerGun* playerGun;

	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];

public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Render() const override;
	virtual void Update(const float deltaTime) override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif // SCENE3_H

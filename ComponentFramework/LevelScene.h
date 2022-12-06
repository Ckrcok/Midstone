#ifndef LevelScene_H
#define LevelScene_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "Skybox.h"
#include "Collision.h"
#include "Wall.h"
#include "EnemyActor.h"
#include "PlayerGun.h"

using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Actor;
// class Mesh; --> CameraActor handles this now
class Shader;
// class Texture; --> CameraActor handles this now

class LevelScene : public Scene
{
private:
	vector<Wall*> theWalls;
	vector<EnemyActor*> enemies;
	Trackball* trackball;
	CameraActor* camera;

	Actor* sphere;
	Actor* cube;
	Mesh* mesh;
	Mesh* meshCube;
	Shader* shader;
	Shader* shaderCube;
	Texture* texture;

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;

	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];


	Vec3 rotationVec = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 test = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 resultPlayer = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerPlayer = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerPlayer = Vec3(0.0f, 0.0f, 0.0f);

	Vec3 resultB = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerB = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerB = Vec3(0.0f, 0.0f, 0.0f);
	PlayerGun* playerGun;

	Box* playerColliderBox = new Box(test, minCornerPlayer, maxCornerPlayer); //= Box(minCornerA, maxCornerA);
	Box* blueBox = new Box(test, minCornerB, maxCornerB);//= Box(minCornerB, maxCornerB);
	short int isDoor = 1;
	bool hasWeapon = false;
	bool hasHealth = false;
	bool hasKey = false;


public:
	explicit LevelScene();
	virtual ~LevelScene();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // LevelScene_H

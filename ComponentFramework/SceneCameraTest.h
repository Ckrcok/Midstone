#ifndef SCENECAMERATEST_H
#define SCENECAMERATEST_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "CameraActorFPS.h"
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


class SceneCameraTest : public Scene {
private:

	//vector<Wall*> theWalls;

	Trackball* trackball;
	//CameraActor* camera;
	CameraActorFPS* cameraFPS;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;

	Actor* sphere;
	Actor* objNegX;
	Actor* objPosX;
	Actor* objNegY;
	Actor* objPosY;
	Actor* objNegZ;
	Actor* objPosZ;
	Actor* lightSource1;
	Actor* cube;

	PlayerGun* playerGun;
	//Mesh* mesh; --> CameraActor handles this now
	Shader* shader;
	Shader* shaderCube;
	/*Texture* texture; --> CameraActor handles these now
	Matrix4 projectionMatrix; 
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;*/
	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];
	Matrix4 modelMatrix;
	
public:
	explicit SceneCameraTest();
	virtual ~SceneCameraTest();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENECAMERATEST_H
#ifndef SCENE2_H
#define SCENE2_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "Skybox.h"
#include "Collision.h"
#include "Wall.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Actor;
// class Mesh; --> CameraActor handles this now
class Shader;
// class Texture; --> CameraActor handles this now


class Scene2 : public Scene {
private:

	//vector<Wall*> theWalls;

	Trackball* trackball;
	CameraActor* camera;

	Actor* sphere;
	Actor* cube;
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
	
public:
	explicit Scene2();
	virtual ~Scene2();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE2_H
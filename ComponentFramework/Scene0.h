#ifndef Scene0_H
#define Scene0_H
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

class Scene0 : public Scene
{
private:
	vector<Wall*> theWalls;

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



	Vec3 test = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 resultA = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerA = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerA = Vec3(0.0f, 0.0f, 0.0f);

	Vec3 resultB = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 minCornerB = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 maxCornerB = Vec3(0.0f, 0.0f, 0.0f);

	Box* redBox; //= Box(minCornerA, maxCornerA);
	Box* blueBox;//= Box(minCornerB, maxCornerB);


public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // Scene0_H

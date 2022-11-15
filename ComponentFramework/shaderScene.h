#ifndef shaderScene_H
#define shaderScene_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

/// Forward declarations
union SDL_Event;
class Actor;
class Mesh;
class Shader;
class Texture;


class shaderScene : public Scene {
private:
	Actor* sphere;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	Vec3 lightPos[10];
	Vec4 diffuse[10];
	Vec4 specular[10];

public:
	explicit shaderScene();
	virtual ~shaderScene();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // shaderScene_H
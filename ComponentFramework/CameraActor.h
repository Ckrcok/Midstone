#pragma once
#include "Actor.h"
#include "Trackball.h"
#include <SDL.h>
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"

using namespace MATH;

class CameraActor : public Actor
{
public:
	CameraActor(Component* parent_);
	~CameraActor();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool OnCreate() override;
	void OnDestroy() override;
	void Render() const override;
	inline Matrix4 GetProjectionMatrix() { return projectionMatrix; }
	inline Matrix4 GetViewMatrix() { return viewMatrix; }

	inline Matrix4 GetTranslationMatrix() { return translationMatrix; }
	inline void SetTranslationMatrix(const Matrix4& translationMatrix_) { translationMatrix = translationMatrix_; }
	inline Matrix4 GetRotationMatrix() { return rotationMatrix; }
	inline void SetRotationMatrix(const Matrix4& rotationMatrix_) { rotationMatrix = rotationMatrix_; }
	Skybox* GetSkyBox() { return skybox; }



private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;
	Trackball* trackball;
	Skybox* skybox;

};


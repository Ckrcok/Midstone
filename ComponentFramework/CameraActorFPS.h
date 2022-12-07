#pragma once
#include "Actor.h"
#include "Trackball.h"
#include <SDL.h>
#include <cmath>
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"


using namespace MATH;

class CameraActorFPS : public Actor
{

private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;
	Skybox* skybox;
	Vec3 CameraActorPosition;
	float cameraSpeed;
	//Matrix4 worldMatrix;
	//Matrix4 FPSViewMatrix;
	Matrix4 LookAtFPS(	const float positionX,	const float positionY,	const float positionZ,
						const float targetX,	const float targetY,	const float targetZ,
						const float worldUpX,	const float worldUpY,	const float worldUpZ);

	Matrix4 LookAtFPS(const Vec3 position, const Vec3 target, const Vec3 worldUp);

	//static Matrix4 FPScamera(Vec3 CameraActorPosition_, float cameraPitch, float cameraYaw);
	

	Vec3 cameraPositionVec;
	Vec3 cameraOrientationVec;
	Vec3 cameraUpDirVec;
	
	float mouseRotX;
	float mouseRotY;
	int mouseRelX;
	int mouseRelY;
	float cameraPitch = 0.0f;
	float cameraYaw = 0.0f;
	float mouseSensitivity;
	
public:
	CameraActorFPS(Component* parent_);
	~CameraActorFPS();
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
	inline Vec3 GetCameraFPSOrientation() { return cameraOrientationVec; }
	inline Vec3 GetCameraFPSPos() { return cameraPositionVec; }
};


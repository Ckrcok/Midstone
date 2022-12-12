#pragma once
#include "Actor.h"
#include "Trackball.h"
#include <SDL.h>
#include <cmath>
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"
#include "Shader.h"

using namespace MATH;

class Shader;

class CameraActorFPS : public Actor
{
// create private variables
private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;
	Matrix4 gunModelMatrix;
	Skybox* skybox;
	Vec3 CameraActorPosition;
	float cameraSpeed;

	Shader* shader;

	Actor* cameraAttachment;

	// custom look at function to create a first person view camera
	Matrix4 LookAtFPS(	const float positionX,	const float positionY,	const float positionZ,
						const float targetX,	const float targetY,	const float targetZ,
						const float worldUpX,	const float worldUpY,	const float worldUpZ);

	Matrix4 LookAtFPS(const Vec3 position, const Vec3 target, const Vec3 worldUp);

	// first person camera matrices
	Matrix4 translationLookAt;
	Matrix4 rotationLookAt;
	Matrix4 LookAtFPSMatrix;

	// first person camera vectors
	Vec3 cameraPositionVec;
	Vec3 cameraOrientationVec;
	Vec3 cameraUpDirVec;
	Vec3 cameraFront;
	
	// camera rotation variables 
	float mouseRotX;
	float mouseRotY;
	int mouseRelX;
	int mouseRelY;
	float cameraPitch = 0.0f;
	float cameraYaw = -90.0f;
	float mouseSensitivity;


public:
	CameraActorFPS(Component* parent_);
	~CameraActorFPS();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(float deltaTime);
	void Render() const override;

	// set initial motion to false
	bool MouseMotion = false;

	// getters & setters
	inline Matrix4 GetProjectionMatrix() { return projectionMatrix; }
	inline Matrix4 GetViewMatrix() { return viewMatrix; }
	inline Matrix4 GetTranslationMatrix() { return translationMatrix; }
	inline void SetTranslationMatrix(const Matrix4& translationMatrix_) { translationMatrix = translationMatrix_; }
	inline Matrix4 GetRotationMatrix() { return rotationMatrix; }
	inline void SetRotationMatrix(const Matrix4& rotationMatrix_) { rotationMatrix = rotationMatrix_; }
	Skybox* GetSkyBox() { return skybox; }
	inline Vec3 GetCameraFPSOrientation() { return cameraOrientationVec; }
	inline Vec3 GetCameraFPSPos() { return cameraPositionVec; }
	inline Vec3 GetCameraFront() { return cameraFront; }
	Actor* GetCameraAttachment() { return cameraAttachment; }
	inline Matrix4 GetCameraRotationMatrix() { return rotationLookAt; };
	inline Matrix4 GetCameraTranslationMatrix() { return translationLookAt; }
	inline Matrix4 GetCameraFPSLookAt() { return LookAtFPSMatrix; }

	// set facing Wall value and keyboard entry
	bool isFacingWall = false;
	char lastTypedKey = 'n';
};


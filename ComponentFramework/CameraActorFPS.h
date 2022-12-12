#pragma once

// Basic include
#include <SDL.h>

#include "Actor.h"
#include "Trackball.h"
#include <cmath>
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"
#include "Shader.h"

// Namespace
using namespace MATH;

// Using class Shader for a special include (fixed bugs)
class Shader;

class CameraActorFPS : public Actor
{
private:
	// Projection Matrices
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;
	Matrix4 gunModelMatrix;

	// Skybox
	Skybox* skybox;

	// Camera
	Actor* cameraAttachment;
	Vec3 CameraActorPosition;
	float cameraSpeed;

	// Shader
	Shader* shader;

	// Matrix functions
	Matrix4 LookAtFPS(const float positionX, const float positionY, const float positionZ,
		const float targetX, const float targetY, const float targetZ,
		const float worldUpX, const float worldUpY, const float worldUpZ);

	Matrix4 LookAtFPS(const Vec3 position, const Vec3 target, const Vec3 worldUp);

	// Matrices
	Matrix4 translationLookAt;
	Matrix4 rotationLookAt;
	Matrix4 LookAtFPSMatrix;

	// Camera positions
	Vec3 cameraPositionVec;
	Vec3 cameraOrientationVec;
	Vec3 cameraUpDirVec;
	Vec3 cameraFront;

	// Mouse variables
	float mouseRotX;
	float mouseRotY;
	int mouseRelX;
	int mouseRelY;
	float cameraPitch = 0.0f;
	float cameraYaw = -90.0f;
	float mouseSensitivity;

public:
	// Constructors
	CameraActorFPS(Component* parent_);
	~CameraActorFPS();

	// Basic functions
	void HandleEvents(const SDL_Event& sdlEvent);
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(float deltaTime);
	void Render() const override;

	// Booleans
	bool MouseMotion = false;
	bool isFacingWall = false;

	// Last typed key character
	char lastTypedKey = 'n';	//Being lazy yes, but this needs to work

	// Set functions
	inline void SetTranslationMatrix(const Matrix4& translationMatrix_) { translationMatrix = translationMatrix_; }
	inline void SetRotationMatrix(const Matrix4& rotationMatrix_) { rotationMatrix = rotationMatrix_; }

	// Get functions (matrices)
	inline Matrix4 GetProjectionMatrix() { return projectionMatrix; }
	inline Matrix4 GetViewMatrix() { return viewMatrix; }
	inline Matrix4 GetTranslationMatrix() { return translationMatrix; }
	inline Matrix4 GetRotationMatrix() { return rotationMatrix; }

	// Get function (skybox)
	Skybox* GetSkyBox() { return skybox; }

	// Get functions (camera)
	inline Vec3 GetCameraFPSOrientation() { return cameraOrientationVec; }
	inline Vec3 GetCameraFPSPos() { return cameraPositionVec; }
	inline Vec3 GetCameraFront() { return cameraFront; }
	Actor* GetCameraAttachment() { return cameraAttachment; }
	inline Matrix4 GetCameraRotationMatrix() { return rotationLookAt; };
	inline Matrix4 GetCameraTranslationMatrix() { return translationLookAt; }
	inline Matrix4 GetCameraFPSLookAt() { return LookAtFPSMatrix; }
};

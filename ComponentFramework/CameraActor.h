#pragma once
#include <SDL.h>

#include "Actor.h"
#include "Trackball.h"
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"
//#include "PlayerGun.h"

using namespace MATH;

class CameraActor : public Actor
{
private:
	//PlayerGun* playerGun;

public:
	Vec3 cameraPositionTracker = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 cameraRotationTracker = Vec3(0.0f, 0.0f, 0.0f);

	bool isFacingWall = false;
	CameraActor(Vec3 spawnPos_, Component* parent_);
	~CameraActor();

	void HandleEvents(const SDL_Event& sdlEvent);
	void Update(float deltaTime);
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

	inline Vec3 GetCameraActorPosition()
	{
		float cameraActorPosX = GetViewMatrix()[12];
		float cameraActorPosY = GetViewMatrix()[13];
		float cameraActorPosZ = GetViewMatrix()[14];

		CameraActorPosition = Vec3(cameraActorPosX, cameraActorPosY, cameraActorPosZ);

		// if all zero
		if (cameraActorPosX == 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ == 0.0f)
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13], GetViewMatrix()[14]);

		//if none zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ != 0.0f)
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14] * -1.0f);

		// if cameraActorPosXis zero, cameraActorPosY & cameraActorPosZ not zero
		else if (cameraActorPosX == 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ != 0.0f)
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14] * -1.0f);

		// if cameraActorPosY is zero, cameraActorPosX & cameraActorPosZ not zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ != 0.0f)
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13], GetViewMatrix()[14] * -1.0f);

		// if cameraActorPosZ is zero, cameraActorPosX & cameraActorPosY not zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ == 0.0f)
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14]);

		// if cameraActorPosX & cameraActorPosY are zero, cameraActorPosZ not zero
		else if (cameraActorPosX == 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ != 0.0f)
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13], GetViewMatrix()[14] * -1.0f);

		// if cameraActorPosX & cameraActorPosZ are zero, cameraActorPosY not zero
		else if (cameraActorPosX == 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ == 0.0f)
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14]);

		// if cameraActorPosY & cameraActorPosZ are zero, cameraActorPosX not zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ == 0.0f)
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13], GetViewMatrix()[14]);
	}

	inline Vec3 GetPlayerPosition() { return GetCameraActorPosition(); }

private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 rotationMatrix;
	Matrix4 translationMatrix;

	Trackball* trackball;
	Skybox* skybox;

	Vec3 CameraActorPosition;
};

#pragma once
#include "Actor.h"
#include "Trackball.h"
#include <SDL.h>
#include <cmath>
#include "MMath.h"
#include "Matrix.h"
#include "Skybox.h"


using namespace MATH;

class CameraActor : public Actor
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
	inline Vec3 GetCameraOrientation() { return cameraOrientationVec; }
	//inline Matrix4 GetFPSviewMatrix() { return FPSViewMatrix; }

	inline Vec3 GetCameraActorPosition()
	{
		float cameraActorPosX = GetViewMatrix()[12];
		float cameraActorPosY = GetViewMatrix()[13];
		float cameraActorPosZ = GetViewMatrix()[14];

		CameraActorPosition = Vec3(cameraActorPosX, cameraActorPosY, cameraActorPosZ);

		// if all zero
		if (cameraActorPosX == 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ == 0.0f)
		{
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13], GetViewMatrix()[14]);
		}

		//if none zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ != 0.0f)
		{
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14] * -1.0f);
		}

		// if cameraActorPosXis zero, cameraActorPosY & cameraActorPosZ not zero
		else if (cameraActorPosX == 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ != 0.0f)
		{
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14] * -1.0f);
		}

		// if cameraActorPosY is zero, cameraActorPosX & cameraActorPosZ not zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ != 0.0f)
		{
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13], GetViewMatrix()[14] * -1.0f);
		}

		// if cameraActorPosZ is zero, cameraActorPosX & cameraActorPosY not zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ == 0.0f)
		{
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14]);
		}

		// if cameraActorPosX & cameraActorPosY are zero, cameraActorPosZ not zero
		else if (cameraActorPosX == 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ != 0.0f)
		{
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13], GetViewMatrix()[14] * -1.0f);
		}

		// if cameraActorPosX & cameraActorPosZ are zero, cameraActorPosY not zero
		else if (cameraActorPosX == 0.0f && cameraActorPosY != 0.0f && cameraActorPosZ == 0.0f)
		{
			return Vec3(GetViewMatrix()[12], GetViewMatrix()[13] * -1.0f, GetViewMatrix()[14]);
		}

		// if cameraActorPosY & cameraActorPosZ are zero, cameraActorPosX not zero
		else if (cameraActorPosX != 0.0f && cameraActorPosY == 0.0f && cameraActorPosZ == 0.0f)
		{
			return Vec3(GetViewMatrix()[12] * -1.0f, GetViewMatrix()[13], GetViewMatrix()[14]);
		}
	}

	inline Vec3 GetPlayerPosition() { return GetCameraActorPosition(); }

};


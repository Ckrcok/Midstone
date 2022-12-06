#include "CameraActor.h"
#include "MMath.h"
#include "Debug.h"

using namespace MATH;

CameraActor::CameraActor(Component* parent_) :Actor(parent_)
{
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	rotationMatrix = MMath::rotate(0.0f, (const Vec3(0.0f, 1.0f, 0.0f)));
	translationMatrix = MMath::translate((const Vec3(0.0f, 0.0f, 0.0f)));
	
	// initial cameraPosition is at spawn position
	cameraPositionVec = Vec3(0.0f, 0.0f, 0.0f);
	cameraOrientationVec = VMath::normalize(Vec3(0.0f, 0.0f, -1.0f));
	cameraUpDirVec = VMath::normalize(Vec3(0.0f, 1.0f, 0.0f));

	cameraSpeed = 0.2f;
	//viewMatrix = rotationMatrix * translationMatrix;
}

//Matrix4 CameraActor::FPScamera(Vec3 CameraActorPosition_, float cameraPitch, float cameraYaw)
//{
//	if (cameraPitch <= -90.0f) cameraPitch = -85.0f;
//	if (cameraPitch >= 90.0f) cameraPitch = 85.0f;
//
//	if (cameraYaw <= 0.0f) cameraYaw = 1.0f;
//	if (cameraYaw >= 360.0f) cameraYaw = 355.0f;
//
//	float cameraPitchR	= cameraPitch	* DEGREES_TO_RADIANS;
//	float cameraYawR	= cameraYaw		* DEGREES_TO_RADIANS;
//
//	float cosCameraPitch	= cos(cameraPitchR);
//	float sinCameraPitch	= sin(cameraPitchR);
//	float cosCameraYaw		= cos(cameraYawR);
//	float sinCameraYaw		= sin(cameraYawR);
//
//	Vec3 side =		{ cosCameraYaw, 0, -sinCameraYaw };
//	Vec3 up =		{ sinCameraYaw * sinCameraPitch, cosCameraPitch, cosCameraYaw * sinCameraPitch };
//	Vec3 front =	{ sinCameraYaw * cosCameraPitch, -sinCameraPitch, cosCameraPitch * cosCameraYaw };
//
//	Matrix4 FPSViewMatrix =
//	{
//						side.x,										up.x,									front.x,						0,
//						side.y,										up.y,									front.y,						0,
//						side.z,										up.z,									front.z,						0,
//			-VMath::dot(side, CameraActorPosition_),	-VMath::dot(up, CameraActorPosition_),	-VMath::dot(front, CameraActorPosition_),	1
//	};
//
//	return FPSViewMatrix;
//}


// Create the view frustum with a First Person LookAt function - float constructor
Matrix4 CameraActor::LookAtFPS(const float positionX, const float positionY, const float positionZ,
	const float targetX, const float targetY, const float targetZ,
	const float worldUpX, const float worldUpY, const float worldUpZ)
{
	Vec3 position (positionX, positionY, positionZ);
	Vec3 target (targetX, targetY, targetZ);
	Vec3 worldUp (worldUpX, worldUpY, worldUpZ);

	Vec3 front	= VMath::normalize(position - target);

	Vec3 side	= VMath::normalize(VMath::cross(VMath::normalize(worldUp), front));

	Vec3 up		= VMath::cross(front, side);

	Matrix4 translationLookAt;

		translationLookAt[0]  = 1.0f;
		translationLookAt[1]  = 0.0f;
		translationLookAt[2]  = 0.0f;
		translationLookAt[3]  = 0.0f;
		translationLookAt[4]  = 0.0f;
		translationLookAt[5]  = 1.0f;
		translationLookAt[6]  = 0.0f;
		translationLookAt[7]  = 0.0f;
		translationLookAt[8]  = 0.0f;
		translationLookAt[9]  = 0.0f;
		translationLookAt[10] = 1.0f;
		translationLookAt[11] = 0.0f;
		translationLookAt[12] = -position.x;
		translationLookAt[13] = -position.y;
		translationLookAt[14] = -position.z;
		translationLookAt[15] = 1.0f;


	Matrix4 rotationLookAt;
	
		rotationLookAt[0]  = side.x;
		rotationLookAt[1]  = up.x;
		rotationLookAt[2]  = front.x;
		rotationLookAt[3]  = 0.0f;
		rotationLookAt[4]  = side.y;
		rotationLookAt[5]  = up.y;
		rotationLookAt[6]  = front.y;
		rotationLookAt[7]  = 0.0f;
		rotationLookAt[8]  = side.z;
		rotationLookAt[9]  = up.z;
		rotationLookAt[10] = front.z;
		rotationLookAt[11] = 0.0f;
		rotationLookAt[12] = 0.0f;
		rotationLookAt[13] = 0.0f;
		rotationLookAt[14] = 0.0f;
		rotationLookAt[15] = 1.0f;

	Matrix4 LookAtFPSMatrix = rotationLookAt * translationLookAt;
	return LookAtFPSMatrix;
}

// Create the view frustum with a First Person Look at function - vector constructor
Matrix4 CameraActor::LookAtFPS(const Vec3 position, const Vec3 target, const Vec3 worldUp) {
	return LookAtFPS(position.x, position.y, position.z, target.x, target.y, target.z, worldUp.x, worldUp.y, worldUp.z);
}

void CameraActor::HandleEvents(const SDL_Event& sdlEvent)
{
	SDL_PumpEvents();  // make sure we have the latest mouse & keyboard state.
	SDL_SetRelativeMouseMode(SDL_TRUE); // Set relative mouse mode for First Person view
	bool MouseMotion = false;
	
	// Camera Orientation Vector (camera is looking at:)
	Vec3 cameraFront;
	cameraFront.x = cos(cameraPitch * DEGREES_TO_RADIANS) * cos(cameraYaw * DEGREES_TO_RADIANS);
	cameraFront.y = sin(cameraPitch * DEGREES_TO_RADIANS);
	cameraFront.z = cos(cameraPitch * DEGREES_TO_RADIANS) * sin(cameraYaw * DEGREES_TO_RADIANS);
	cameraOrientationVec = VMath::normalize(cameraFront);
	

	// Create the view matrix with First Person LookAt function
	viewMatrix = LookAtFPS(cameraPositionVec, cameraPositionVec + cameraOrientationVec, cameraUpDirVec);

	// CAMERA MOVEMENT on XY Plane (45-90 degree movement)
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
	{
		// Move forward & backwards
		if (keyboard_state_array[SDL_SCANCODE_W] && !(keyboard_state_array[SDL_SCANCODE_S]))
		{
			cameraPositionVec += cameraSpeed * cameraOrientationVec;
			cameraPositionVec.y = 0.0f;
		}
		else if (!keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_S])
		{
			cameraPositionVec += cameraSpeed * -cameraOrientationVec;
			cameraPositionVec.y = 0.0f;
		}

		if (keyboard_state_array[SDL_SCANCODE_D] && !keyboard_state_array[SDL_SCANCODE_A])
		{
			cameraPositionVec += cameraSpeed * VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
			cameraPositionVec.y = 0.0f;
		}
		else if (!keyboard_state_array[SDL_SCANCODE_D] && keyboard_state_array[SDL_SCANCODE_A])
		{
			cameraPositionVec += cameraSpeed * -VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
			cameraPositionVec.y = 0.0f;
		}
	}
	

	//switch (sdlEvent.type) {
	//case SDL_KEYDOWN:

	//	// MOVE - STRAFE
	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
	//	{
	//		cameraPositionVec += cameraSpeed * cameraOrientationVec;		
	//		cameraPositionVec.y = 0.0f;
	//	}
	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
	//	{
	//		cameraPositionVec += cameraSpeed * -cameraOrientationVec;
	//		cameraPositionVec.y = 0.0f;
	//		//SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f) * cameraSpeed));
	//	}
	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
	//	{
	//		cameraPositionVec += cameraSpeed * -VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
	//		cameraPositionVec.y = 0.0f;
	//		//SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(1.0f, 0.0f, 0.0f) * cameraSpeed));
	//	}
	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
	//	{
	//		cameraPositionVec += cameraSpeed * VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
	//		cameraPositionVec.y = 0.0f;
	//		//SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(-1.0f, 0.0f, 0.0f) * cameraSpeed));
	//	}

	//	// Elevate
	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_R)
	//	{
	//		cameraPositionVec += cameraSpeed * cameraUpDirVec;
	//		//SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, -1.0f, 0.0f) * cameraSpeed));
	//	}
	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_F)
	//	{
	//		cameraPositionVec += cameraSpeed * -cameraUpDirVec;
	//		//SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, 1.0f, 0.0f) * cameraSpeed));
	//	}

	//	// LOOK AROUND --- solve the issue with tilting
	//	float rotateConstant = 10.0f;

	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
	//	{
	//		SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(-1.0f, 0.0f, 0.0f)));
	//	}
	//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
	//	{
	//		SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(1.0f, 0.0f, 0.0f)));
	//	}
	//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
	//	{
	//		SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(0.0f, -1.0f, 0.0f)));
	//	}
	//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
	//	{
	//		SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(0.0f, 1.0f, 0.0f)));
	//	}


	//	// sprint
	//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LSHIFT)
	//	{
	//		if (SDL_RELEASED)
	//		{
	//			cameraSpeed = 1.0f;
	//		}

	//		else if (SDL_PRESSED)
	//		{
	//			cameraSpeed = 2.0f;
	//		}

	//	}
	//	
	//	break;

	//}

	// Mouse Inputs
	int mouseX, mouseY;
	Uint32 mouseButtons;
	mouseSensitivity = 1.0f;	

	mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);	

	SDL_Log("Mouse cursor is at %d, %d", mouseX, mouseY);
	if ((mouseButtons & SDL_BUTTON_LMASK) != 0) 
	{
		//SDL_Log("Mouse Button 1 (left) is pressed.");
	}

	if ((mouseButtons & SDL_BUTTON_RMASK) != 0)
	{
		//SDL_Log("Mouse Button 2 (right) is pressed.");
	}

	// Check Mouse Movement
	if (sdlEvent.type == SDL_MOUSEMOTION) 
	{		
		MouseMotion = true;
		mouseRelX = sdlEvent.motion.xrel * mouseSensitivity;
		mouseRelY = sdlEvent.motion.yrel * mouseSensitivity;

		if (MouseMotion)
		{
			MouseMotion = false;
			cameraYaw += mouseRelX;
			cameraPitch -= mouseRelY;

			if (cameraPitch >  89.0f) cameraPitch =  89.0f;
			if (cameraPitch < -89.0f) cameraPitch = -89.0f;
			/*if (cameraYaw <= 0.0f) cameraYaw = 1.0f;
			if (cameraYaw >= 360.0f) cameraYaw = 355.0f;*/
			
			std::cout << "Mouse X relative: " << mouseRelX << " Mouse Y relative : " << mouseRelY << std::endl;

		}

	}

}

bool CameraActor::OnCreate()
{
	/*skybox = new Skybox("textures/skybox/tron_rt_px.png", "textures/skybox/tron_up_py.png", "textures/skybox/tron_ft_pz.png",
		"textures/skybox/tron_lf_nx.png", "textures/skybox/tron_dn_ny.png", "textures/skybox/tron_bk_nz.png");
	return skybox->OnCreate();*/
	return true;
}

void CameraActor::OnDestroy()
{
	/*skybox->OnDestroy();
	delete skybox;*/
}

CameraActor::~CameraActor()
{

}

void CameraActor::Render() const
{
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	/*glUseProgram(skybox->GetShader()->GetProgram());
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("cameraRotationMatrix"), 1, GL_FALSE, rotationMatrix);
	skybox->Render();
	glUseProgram(0);*/
}
#include "CameraActorFPS.h"
#include "MMath.h"
#include "Debug.h"

using namespace MATH;

CameraActorFPS::CameraActorFPS(Component* parent_) :Actor(parent_)
{
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	//rotationMatrix = MMath::rotate(0.0f, (const Vec3(0.0f, 1.0f, 0.0f)));
	//translationMatrix = MMath::translate((const Vec3(0.0f, 0.0f, 0.0f)));
	
	// initial cameraPosition is at spawn position
	cameraPositionVec = Vec3(0.0f, 0.0f, 0.0f);
	cameraOrientationVec = VMath::normalize(Vec3(0.0f, 0.0f, -1.0f));
	cameraUpDirVec = VMath::normalize(Vec3(0.0f, 1.0f, 0.0f));

	cameraSpeed = 0.2f;
	//viewMatrix = rotationMatrix * translationMatrix;
}

 //Create the view frustum with a First Person LookAt function - float constructor
Matrix4 CameraActorFPS::LookAtFPS(const float positionX, const float positionY, const float positionZ,
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
Matrix4 CameraActorFPS::LookAtFPS(const Vec3 position, const Vec3 target, const Vec3 worldUp) {
	return LookAtFPS(position.x, position.y, position.z, target.x, target.y, target.z, worldUp.x, worldUp.y, worldUp.z);
}

void CameraActorFPS::HandleEvents(const SDL_Event& sdlEvent)
{
	SDL_PumpEvents();  // make sure we have the latest mouse & keyboard state.
	SDL_SetRelativeMouseMode(SDL_TRUE); // Set relative mouse mode for First Person view
	bool MouseMotion = false;

	// Camera Orientation Vector (camera is looking at:)
	Vec3 cameraFront;
	cameraFront.x = cos(cameraPitch * DEGREES_TO_RADIANS) * cos(cameraYaw * DEGREES_TO_RADIANS);
	cameraFront.y = sin(cameraPitch * DEGREES_TO_RADIANS);
	cameraFront.z = cos(cameraPitch * DEGREES_TO_RADIANS) * sin(cameraYaw * DEGREES_TO_RADIANS);
	/*cameraFront.x = -sin(cameraYaw * DEGREES_TO_RADIANS);
	cameraFront.y = sin(cameraPitch * DEGREES_TO_RADIANS) * cos(cameraYaw * DEGREES_TO_RADIANS);
	cameraFront.z = -cos(cameraPitch * DEGREES_TO_RADIANS) * cos(cameraYaw * DEGREES_TO_RADIANS);*/
	cameraOrientationVec = VMath::normalize(cameraFront);

	// Create the view matrix with First Person LookAt function
	viewMatrix = LookAtFPS(cameraPositionVec, cameraPositionVec + cameraOrientationVec, cameraUpDirVec);
	//viewMatrix = MMath::lookAt(cameraPositionVec, cameraPositionVec + cameraOrientationVec, cameraUpDirVec); // --- Scott's method

	// CAMERA MOVEMENT on XY Plane (45-90 degree movement)
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
	{
		// Move forward & backwards -- updated method
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
	
	// TODO
	//
	// Sprint
	// cross strafe speed align(normalize)

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
			cameraYaw += mouseRelX * 0.15f;
			cameraPitch -= mouseRelY * 0.15f;

			// clamp upwards-downwards look
			if (cameraPitch >  75.0f) cameraPitch =  75.0f;
			if (cameraPitch < -75.0f) cameraPitch = -75.0f;
			
			std::cout << "Mouse X relative: " << mouseRelX << " Mouse Y relative : " << mouseRelY << std::endl;
		}

	}

}

bool CameraActorFPS::OnCreate()
{
	return true;
}

void CameraActorFPS::OnDestroy()
{

}

CameraActorFPS::~CameraActorFPS()
{

}

void CameraActorFPS::Render() const
{
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	/*glUseProgram(skybox->GetShader()->GetProgram());
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("cameraRotationMatrix"), 1, GL_FALSE, rotationMatrix);
	skybox->Render();
	glUseProgram(0);*/
}
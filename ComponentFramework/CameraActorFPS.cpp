// Basic include
#include "CameraActorFPS.h"
#include "MMath.h"
#include "Debug.h"

using namespace MATH;

CameraActorFPS::CameraActorFPS(Component* parent_) :Actor(parent_)
{
	// Set the projection matrix with the hardcoded values
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	
	// Initial camera vectors
	cameraPositionVec = Vec3(0.0f, 0.0f, 0.0f);
	cameraOrientationVec = VMath::normalize(Vec3(0.0f, 0.0f, -1.0f));
	cameraUpDirVec = VMath::normalize(Vec3(0.0f, 1.0f, 0.0f));

	// Set the camera speed
	cameraSpeed = 0.2f;
}

CameraActorFPS::~CameraActorFPS() {}

bool CameraActorFPS::OnCreate()
{
	// Create and setup the camera attachments
	cameraAttachment = new Actor(nullptr);
	cameraAttachment->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	cameraAttachment->GetMesh()->OnCreate();
	cameraAttachment->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, -5.0f)) * MMath::scale(Vec3(0.3, 0.3, 0.3)));
	cameraAttachment->SetTexture(new Texture());
	cameraAttachment->GetTexture()->LoadImage("textures/white.png");
	cameraAttachment->OnCreate();

	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	// Return true, so that the program can run
	return true;
}

void CameraActorFPS::OnDestroy()
{
	// If cameraAttachment exists, call OnDestroy and delete
	if (cameraAttachment)
	{
		cameraAttachment->OnDestroy();
		delete cameraAttachment;
	}
}

void CameraActorFPS::Update(float deltaTime)
{
	// Set the model matrix of the camera
	cameraAttachment->SetModelMatrix(
		MMath::rotate(this->GetCameraFPSOrientation().x, Vec3(0.0f, 1.0f, 0.0f))
		* MMath::translate(Vec3(0.0f, 0.0f, -5.0f))
		* MMath::scale(Vec3(0.3, 0.3, 0.3)));
}

void CameraActorFPS::Render() const {}

//Create the view frustum with a First Person LookAt function - float constructor
Matrix4 CameraActorFPS::LookAtFPS(const float positionX, const float positionY, const float positionZ,
	const float targetX, const float targetY, const float targetZ,
	const float worldUpX, const float worldUpY, const float worldUpZ)
{
	// Create and set the positions
	Vec3 position(positionX, positionY, positionZ);
	Vec3 target(targetX, targetY, targetZ);
	Vec3 worldUp(worldUpX, worldUpY, worldUpZ);

	// Set the front, side and up vectors
	Vec3 front = VMath::normalize(position - target);
	Vec3 side = VMath::normalize(VMath::cross(VMath::normalize(worldUp), front));
	Vec3 up = VMath::cross(front, side);

	// Translation Look At
	translationLookAt;

	translationLookAt[0] = 1.0f;
	translationLookAt[1] = 0.0f;
	translationLookAt[2] = 0.0f;
	translationLookAt[3] = 0.0f;
	translationLookAt[4] = 0.0f;
	translationLookAt[5] = 1.0f;
	translationLookAt[6] = 0.0f;
	translationLookAt[7] = 0.0f;
	translationLookAt[8] = 0.0f;
	translationLookAt[9] = 0.0f;
	translationLookAt[10] = 1.0f;
	translationLookAt[11] = 0.0f;
	translationLookAt[12] = -position.x;
	translationLookAt[13] = -position.y;
	translationLookAt[14] = -position.z;
	translationLookAt[15] = 1.0f;


	// Rotation Look At
	rotationLookAt;

	rotationLookAt[0] = side.x;
	rotationLookAt[1] = up.x;
	rotationLookAt[2] = front.x;
	rotationLookAt[3] = 0.0f;
	rotationLookAt[4] = side.y;
	rotationLookAt[5] = up.y;
	rotationLookAt[6] = front.y;
	rotationLookAt[7] = 0.0f;
	rotationLookAt[8] = side.z;
	rotationLookAt[9] = up.z;
	rotationLookAt[10] = front.z;
	rotationLookAt[11] = 0.0f;
	rotationLookAt[12] = 0.0f;
	rotationLookAt[13] = 0.0f;
	rotationLookAt[14] = 0.0f;
	rotationLookAt[15] = 1.0f;

	// Create final matrix and return
	Matrix4 LookAtFPSMatrix = rotationLookAt * translationLookAt;
	return LookAtFPSMatrix;
}

// Create the view frustum with a First Person Look at function - vector constructor
Matrix4 CameraActorFPS::LookAtFPS(const Vec3 position, const Vec3 target, const Vec3 worldUp) {
	return LookAtFPS(position.x, position.y, position.z, target.x, target.y, target.z, worldUp.x, worldUp.y, worldUp.z);
}

void CameraActorFPS::HandleEvents(const SDL_Event& sdlEvent)
{
	SDL_PumpEvents();					// Make sure we have the latest mouse & keyboard state.
	SDL_SetRelativeMouseMode(SDL_TRUE);	// Set relative mouse mode for First Person view

	// Camera Orientation Vector (camera is looking at:)
	cameraFront;
	cameraFront.x = cos(cameraPitch * DEGREES_TO_RADIANS) * cos(cameraYaw * DEGREES_TO_RADIANS);
	cameraFront.y = sin(cameraPitch * DEGREES_TO_RADIANS);
	cameraFront.z = cos(cameraPitch * DEGREES_TO_RADIANS) * sin(cameraYaw * DEGREES_TO_RADIANS);
	cameraOrientationVec = VMath::normalize(cameraFront);

	// Create the view matrix with First Person LookAt function
	viewMatrix = LookAtFPS(cameraPositionVec, cameraPositionVec + cameraOrientationVec, cameraUpDirVec);

	// Camera movement on XY Plane 
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	if (sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
	{
		// Move forward & backwards
		if (keyboard_state_array[SDL_SCANCODE_W] && !(keyboard_state_array[SDL_SCANCODE_S]))
		{	//FORWARD

			if (isFacingWall == true)
			{
				if (lastTypedKey != 'w')
				{
					cameraPositionVec += cameraSpeed * cameraOrientationVec;
					cameraPositionVec.y = 0.0f;
					lastTypedKey = 'w';
					isFacingWall = false;
				}

				// Debug
				printf("Colliding in  the same direction");
			}
			else if (isFacingWall == false)
			{
				cameraPositionVec += cameraSpeed * cameraOrientationVec;
				cameraPositionVec.y = 0.0f;
				lastTypedKey = 'w';
			}
		}

		else if (!keyboard_state_array[SDL_SCANCODE_W] && keyboard_state_array[SDL_SCANCODE_S])
		{	//BACKWARDS
			if (isFacingWall == true)
			{
				if (lastTypedKey != 's')
				{
					cameraPositionVec += cameraSpeed * -cameraOrientationVec;
					cameraPositionVec.y = 0.0f;
					lastTypedKey = 's';
					isFacingWall = false;

				}

				// Debug
				printf("Colliding in  the same direction");
			}
			else if (isFacingWall == false)
			{
				cameraPositionVec += cameraSpeed * -cameraOrientationVec;
				cameraPositionVec.y = 0.0f;
				lastTypedKey = 's';
			}
		}

		if (keyboard_state_array[SDL_SCANCODE_D] && !keyboard_state_array[SDL_SCANCODE_A])
		{	//RIGHT
			if (isFacingWall == true)
			{
				if (lastTypedKey != 'd')
				{
					cameraPositionVec += cameraSpeed * VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
					cameraPositionVec.y = 0.0f;
					lastTypedKey = 'd';
					isFacingWall = false;
				}

				// Debug
				printf("Colliding in  the same direction");
			}
			else if (isFacingWall == false)
			{
				cameraPositionVec += cameraSpeed * VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
				cameraPositionVec.y = 0.0f;
				lastTypedKey = 'd';
			}
		}

		else if (!keyboard_state_array[SDL_SCANCODE_D] && keyboard_state_array[SDL_SCANCODE_A])
		{	//LEFT

			if (isFacingWall == true)
			{
				if (lastTypedKey != 'a')
				{
					cameraPositionVec += cameraSpeed * -VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
					cameraPositionVec.y = 0.0f;
					lastTypedKey = 'a';
					isFacingWall = false;

				}

				// Debug
				printf("Colliding in  the same direction");
			}
			else if (isFacingWall == false)
			{
				cameraPositionVec += cameraSpeed * -VMath::normalize(VMath::cross(cameraOrientationVec, cameraUpDirVec));
				cameraPositionVec.y = 0.0f;
				lastTypedKey = 'a';
			}
		}
	}
	
	// Mouse Inputs
	int mouseX, mouseY;
	Uint32 mouseButtons;
	mouseSensitivity = 1.0f;

	mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);

	// Debug for mouse coordinates
	//SDL_Log("Mouse cursor is at %d, %d", mouseX, mouseY);

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

			// Clamp upwards-downwards look
			if (cameraPitch > 75.0f) cameraPitch = 75.0f;
			if (cameraPitch < -75.0f) cameraPitch = -75.0f;

			// Debug for the mouse relative positions
			//std::cout << "Mouse X relative: " << mouseRelX << " Mouse Y relative : " << mouseRelY << std::endl;
		}

	}

}

bool CameraActorFPS::OnCreate()
{
	return true;
}

void CameraActorFPS::OnDestroy(){}

void CameraActorFPS::Update(float deltaTime){}

CameraActorFPS::~CameraActorFPS(){}

void CameraActorFPS::Render() const{}

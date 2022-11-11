#include "CameraActor.h"
#include "MMath.h"
#include "Debug.h"

using namespace MATH;

CameraActor::CameraActor(Vec3 spawnPos_, Component* parent_) :Actor(parent_)
{
	trackball = new Trackball();
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	rotationMatrix = MMath::rotate(0.0f, (const Vec3(0.0f, 1.0f, 0.0f)));
	translationMatrix = MMath::translate((const Vec3(0.0f, 0.0f, 0.0f)));

	SetTranslationMatrix(translationMatrix *= MMath::translate(spawnPos_)); // we should be careful with this!!!

	//playerGun = new PlayerGun(Vec3(1, -1, 1), 0.0f, Vec3(0, 0, 0), this, NULL);
}

void CameraActor::HandleEvents(const SDL_Event& sdlEvent)
{
	trackball->HandleEvents(sdlEvent);
	//rotationMatrix = trackball->getMatrix4();
	viewMatrix = rotationMatrix * translationMatrix;

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:

		// MOVE - STRAFE
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, -1.0f)));
			// elapsed time 
			// hookes law
			// spring movement
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(1.0f, 0.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(-1.0f, 0.0f, 0.0f)));
		}

		// Elevate
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_R)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, -1.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_F)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, 1.0f, 0.0f)));
		}



		// LOOK AROUND --- solve the issue with tilting
		float rotateConstant = 10.0f;

		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_UP)
		{
			SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(-1.0f, 0.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_DOWN)
		{
			SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(1.0f, 0.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT)
		{
			SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(0.0f, -1.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			SetRotationMatrix(GetRotationMatrix() *= MMath::rotate(rotateConstant, Vec3(0.0f, 1.0f, 0.0f)));
		}

		/*else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E)
		{
			SetRotationMatrix(GetTranslationMatrix());
			std::cout << "Reset Rotation!" << std::endl;
		}*/

		break;

	}
}

void CameraActor::Update(float deltaTime)
{
	//playerGun->Update(deltaTime);
}

bool CameraActor::OnCreate()
{
	skybox = new Skybox("textures/skybox/tron_rt_px.png", "textures/skybox/tron_up_py.png", "textures/skybox/tron_ft_pz.png",
		"textures/skybox/tron_lf_nx.png", "textures/skybox/tron_dn_ny.png", "textures/skybox/tron_bk_nz.png");
	return skybox->OnCreate();

	//playerGun->OnCreate();
}

void CameraActor::OnDestroy()
{
	if (skybox)
	{
		skybox->OnDestroy();
		delete skybox;
	}

	//if (playerGun)
	//{
	//	playerGun->OnDestroy();
	//	delete playerGun;
	//}
}

CameraActor::~CameraActor()
{
	if (trackball)
		delete trackball;
}

void CameraActor::Render() const
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glUseProgram(skybox->GetShader()->GetProgram());

	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("viewMatrix"), 1, GL_FALSE, rotationMatrix);

	skybox->Render();
	//playerGun->Render();

	glUseProgram(0);
}

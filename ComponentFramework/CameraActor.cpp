#include "CameraActor.h"
#include "MMath.h"
#include "Debug.h"

using namespace MATH;

CameraActor::CameraActor(Component* parent_) :Actor(parent_)
{
	trackball = new Trackball();
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	rotationMatrix = MMath::rotate(0.0f, (const Vec3(0.0f, 1.0f, 0.0f)));
	translationMatrix = MMath::translate((const Vec3(0.0f, 0.0f, -10.0f)));
	viewMatrix = rotationMatrix * translationMatrix;
	translationMatrix.print("Translation");
	rotationMatrix.print("Rotation");
}

void CameraActor::HandleEvents(const SDL_Event& sdlEvent)
{
	trackball->HandleEvents(sdlEvent);
	rotationMatrix = trackball->getMatrix4();
	viewMatrix = rotationMatrix * translationMatrix;

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, -1.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(-1.0f, 0.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
		{
			SetTranslationMatrix(GetTranslationMatrix() *= MMath::translate(Vec3(1.0f, 0.0f, 0.0f)));
		}

		break;

	}
}

bool CameraActor::OnCreate()
{
	skybox = new Skybox("textures/CN_Tower/posx.jpg", "textures/CN_Tower/posy.jpg", "textures/CN_Tower/posz.jpg",
		"textures/CN_Tower/negx.jpg", "textures/CN_Tower/negy.jpg", "textures/CN_Tower/negz.jpg");
	return skybox->OnCreate();
}

void CameraActor::OnDestroy()
{
	skybox->OnDestroy();
	delete skybox;
}

CameraActor::~CameraActor()
{
	if (trackball) delete trackball;
}

void CameraActor::Render() const
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glUseProgram(skybox->GetShader()->GetProgram()); // build a getshader
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->GetShader()->GetUniformID("viewMatrix"), 1, GL_FALSE, rotationMatrix);
	skybox->Render();
	glUseProgram(0);
}
#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"

Scene0::Scene0()
{
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0()
{
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene0::OnCreate()
{
	doorPuzzle = new DoorPuzzle();

	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	return true;

}

void Scene0::OnDestroy()
{
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{
	doorPuzzle->HandleEvents(sdlEvent);

	switch (sdlEvent.type)
	{
	case SDL_KEYDOWN:
		break;

	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void Scene0::Update(const float deltaTime) {}

void Scene0::Render() const
{
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(0);
}

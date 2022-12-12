// Basic include
#include <SDL.h>

#include "SceneManager.h"
#include "Timer.h"
#include "Window.h"

// Extra include
#include "Scene1.h"
#include "Scene3.h"
#include "Scene4.h"
#include "SceneCameraTest.h"
#include "SceneCombination.h"

SceneManager::SceneManager() :
	currentScene(nullptr), window(nullptr), timer(nullptr),
	fps(60), isRunning(false), fullScreen(false)
{
	Debug::Info("Starting the SceneManager", __FILE__, __LINE__);
}

SceneManager::~SceneManager()
{
	if (currentScene)
	{
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}

	if (timer)
	{
		delete timer;
		timer = nullptr;
	}

	if (window)
	{
		delete window;
		window = nullptr;
	}

	Debug::Info("Deleting the SceneManager", __FILE__, __LINE__);
}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {

	window = new Window();
	if (!window->OnCreate(name_, width_, height_))
	{
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}

	timer = new Timer();
	if (timer == nullptr)
	{
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}

	/********************************   Default first scene   ***********************/
	BuildNewScene(SCENE_NUMBER::SCENECAMERATEST);

	return true;
}

/// This is the whole game
void SceneManager::Run()
{
	timer->Start();
	isRunning = true;

	while (isRunning)
	{
		timer->UpdateFrameTicks();

		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();

		HandleEvents();

		SDL_GL_SwapWindow(window->getWindow());
		SDL_Delay(timer->GetSleepTime(fps));
	}
}

void SceneManager::HandleEvents()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_EventType::SDL_QUIT)
		{
			isRunning = false;
			return;
		}
		else if (sdlEvent.type == SDL_KEYDOWN)
		{
			switch (sdlEvent.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				break;

			case SDL_SCANCODE_Q:
				isRunning = false;
				return;
				[[fallthrough]]; /// C17 Prevents switch/case fallthrough warnings
				break;

			case SDL_SCANCODE_F1:
				BuildNewScene(SCENE_NUMBER::SCENE1);
				break;

			case SDL_SCANCODE_F2:
				BuildNewScene(SCENE_NUMBER::SCENECAMERATEST);
				break;

			case SDL_SCANCODE_F3:
				BuildNewScene(SCENE_NUMBER::SCENE3);
				break;

			case SDL_SCANCODE_F4:
				BuildNewScene(SCENE_NUMBER::SCENE4);
				break;

			case SDL_SCANCODE_F5:
				BuildNewScene(SCENE_NUMBER::SCENE4);
				break;

			case SDL_SCANCODE_SPACE:
				BuildNewScene(SCENE_NUMBER::SCENE_COMBINATION);
				break;

			default:
				break;
			}
		}

		if (currentScene == nullptr)
		{
			Debug::FatalError("Failed to initialize Scene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}

		currentScene->HandleEvents(sdlEvent);
	}
}

void SceneManager::BuildNewScene(SCENE_NUMBER scene)
{
	bool status;

	if (currentScene != nullptr)
	{
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene)
	{
	case SCENE_NUMBER::SCENE1:
		currentScene = new Scene1();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENECAMERATEST:
		currentScene = new SceneCameraTest();
		status = currentScene->OnCreate();
		break;


	case SCENE_NUMBER::SCENE3:
		currentScene = new Scene3();
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE4:
		currentScene = new Scene4(window->getWindow());
		status = currentScene->OnCreate();
		break;

	case SCENE_NUMBER::SCENE_COMBINATION:
		currentScene = new SceneCombination();
		status = currentScene->OnCreate();
		break;

	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		break;
	}
}

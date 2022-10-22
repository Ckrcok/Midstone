#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Vector.h"
#include "Plane.h"
#include "Matrix.h"
#include "SceneManager.h"
#include "MMath.h"

#include <vector>
#include <iostream>
#include <SDL.h>
#include "SDL_image.h"

using namespace MATH;
using namespace std;
struct MATH::Plane;

// Forward declarations 
union SDL_Event;

class Scene4 : public Scene
{
private:
	SDL_Window* window;
	float xAxis = 25.0f;
	float yAxis = 15.0f;
	SDL_Renderer* renderer;
	SDL_Surface* surfacePtr;
	SDL_Texture* texturePtr;
	Matrix4 projectionMatrix;
	Matrix4 inverseProjection;

	class Window* windowPtr;

public:
	/**
	Scene4(SDL_Window* sdlWindow_, SceneManager* game_);
	~Scene4();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	bool nextScene() { return false; }
	/**/

	//explicit Scene4(SDL_Window* sdlWindow_, SceneManager* game_);
	explicit Scene4(SDL_Window* sdlWindow_);
	virtual ~Scene4();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Render() const override;
	virtual void Update(const float deltaTime) override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;

	////Game manager need this to get acces to SceneMenu
	//float getxAxis() { return xAxis; }
	//float getyAxis() { return yAxis; }
	//SDL_Window* getWindow() { return window; }
	//Matrix4 getProjectionMatrix() { return projectionMatrix; }
	//Matrix4 getInverseMatrix() { return inverseProjection; }
};

#endif // !SCENE_4_H

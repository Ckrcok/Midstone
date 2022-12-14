#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Run();
	bool Initialize(std::string name_, int width_, int height_);
	void HandleEvents();

private:
	enum class SCENE_NUMBER
	{
		LEVELSCENE = 3,
		SCENE1,
		SCENECAMERATEST,
		SCENE3,
		SCENE4,
		SCENE_COMBINATION
	};

	class Scene* currentScene;
	class Timer* timer;
	class Window* window;

	unsigned int fps;
	bool isRunning;
	bool fullScreen;
	void BuildNewScene(SCENE_NUMBER scene_);
};

#endif // SCENEMANAGER_H

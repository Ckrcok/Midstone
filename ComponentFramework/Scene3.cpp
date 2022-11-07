#include "Scene3.h"

#include "Debug.h"

Scene3::Scene3() : shader(nullptr)
{
	Debug::Info("Created Scene2: ", __FILE__, __LINE__);
	trackball = new Trackball();

	int spawnPos = -2.0f;
	for (int i = 0; i < 1; i++)
	{
		EnemyActor* enemy = new EnemyActor(Vec3(spawnPos, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
		spawnPos += 2;

		enemies.push_back(enemy);
	}
}

Scene3::~Scene3()
{
	Debug::Info("Deleted Scene3: ", __FILE__, __LINE__);
	if (trackball)
		delete trackball;
}

bool Scene3::OnCreate()
{
	Debug::Info("Loading assets Scene3: ", __FILE__, __LINE__);

	camera = new CameraActor(Vec3(0.0f, 0.0f, -10.0f), nullptr);
	camera->OnCreate();

	for (EnemyActor* enemy : enemies) {
		enemy->SetCamera(camera);
		enemy->OnCreate();
	}

	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	lightPos[0] = Vec3(3.0f, 0.0f, -6.5f);
	lightPos[1] = Vec3(-3.0f, 0.0f, -6.5f);
	lightPos[2] = Vec3(0.0f, 3.0f, -6.5f);
	lightPos[3] = Vec3(0.0f, -3.0f, -6.5f);

	diffuse[0] = Vec4(0.6f, 0.0f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.0f, 0.6f, 0.0f, 0.0f);
	diffuse[2] = Vec4(0.0f, 0.0f, 0.6f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];

	return true;
}

void Scene3::OnDestroy()
{
	Debug::Info("Deleting assets Scene3: ", __FILE__, __LINE__);

	if (camera)
	{
		camera->OnDestroy();
		delete camera;
	}

	for (EnemyActor* enemy : enemies)
	{
		if (enemy)
		{
			enemy->OnDestroy();
			delete enemy;
		}
	}
	enemies.clear();

	shader->OnDestroy();
	delete shader;
}

void Scene3::Render() const
{
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera->Render();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());

	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);

	for (EnemyActor* enemy : enemies)
		enemy->Render();

	glUseProgram(0);
}

void Scene3::Update(const float deltaTime)
{
	camera->Update(deltaTime);

	for (EnemyActor* enemy : enemies)
		enemy->Update(deltaTime);

	//cout << "CameraPos Scene: ";
	//camera->GetPosition().print();
}

void Scene3::HandleEvents(const SDL_Event& sdlEvent)
{
	camera->HandleEvents(sdlEvent);

	for (EnemyActor* enemy : enemies)
		enemy->HandleEvents(sdlEvent);
}

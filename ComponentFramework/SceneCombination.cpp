// Basic include
#include "SceneCombination.h"

SceneCombination::SceneCombination()
{
	// Debug information
	Debug::Info("Created SceneCombination: ", __FILE__, __LINE__);

	int spawnPosXOfEnemies = -2.0f;	// Start X position of the enemies 
	for (int i = 0; i < 1; i++)
	{
		// Create enemy
		EnemyActor* enemy = new EnemyActor(Vec3(spawnPosXOfEnemies, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

		spawnPosXOfEnemies += 2;		// Up the x position of the spawn position
		enemies.push_back(enemy);	// Add to the list of enemies
	}
}

SceneCombination::~SceneCombination()
{
	// Debug information
	Debug::Info("Deleted SceneÇombination: ", __FILE__, __LINE__);
}

bool SceneCombination::OnCreate()
{
	// Debug information
	Debug::Info("Loading assets SceneCombination: ", __FILE__, __LINE__);

	// Create camera and call OnCreate
	camera = new CameraActor(Vec3(0.0f, 0.0f, -10.0f), nullptr);
	camera->OnCreate();

	// Create the player gun and call OnCreate
	playerGun = new PlayerGun(Vec3(1.0f, -0.5f, 8.0f), 0.0f, Vec3(0, 0, 0), camera, nullptr);
	playerGun->OnCreate();

	// Set the camera and call OnCreate for every enemy in the list with enemies
	for (EnemyActor* enemy : enemies) {
		enemy->SetCamera(camera);
		enemy->OnCreate();
	}

	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)	// Debug information
		Debug::Error("Can't load shader in SceneCombination", __FILE__, __LINE__);

	// Set light positions
	lightPos[0] = Vec3(3.0f, 0.0f, -6.5f);
	lightPos[1] = Vec3(-3.0f, 0.0f, -6.5f);
	lightPos[2] = Vec3(0.0f, 3.0f, -6.5f);
	lightPos[3] = Vec3(0.0f, -3.0f, -6.5f);

	// Set diffuse values
	diffuse[0] = Vec4(0.6f, 0.0f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.0f, 0.6f, 0.0f, 0.0f);
	diffuse[2] = Vec4(0.0f, 0.0f, 0.6f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	// Set specular values
	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];

	// Return true so program can run
	return true;
}

void SceneCombination::OnDestroy()
{
	// Debug information
	Debug::Info("Deleting assets SceneCombination: ", __FILE__, __LINE__);

	// If camera exists, call OnDestroy and delete
	if (camera)
	{
		camera->OnDestroy();
		delete camera;
	}

	// If shader exists, call OnDestroy and delete
	if (shader)
	{
		shader->OnDestroy();
		delete shader;
	}

	// If player gun exists, call OnDestroy and delete
	if (playerGun)
	{
		playerGun->OnDestroy();
		delete playerGun;
	}

	// Check for every enemy in the list if it exists
	// If so, call OnDestroy and delete
	// After that, clear the list with enemies
	for (EnemyActor* enemy : enemies)
	{
		if (enemy)
		{
			enemy->OnDestroy();
			delete enemy;
		}
	}
	enemies.clear();
}

void SceneCombination::Render() const
{
	// Set the culling and front face variables
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the camera
	camera->Render();

	// Enable depth and culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Set matrices
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());

	// Set uniforms
	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);

	// Render the gun of the player
	playerGun->Render();

	// Render every enemy in the list
	for (EnemyActor* enemy : enemies)
		enemy->Render();

	// Use program 0
	glUseProgram(0);
}

void SceneCombination::Update(const float deltaTime)
{
	// Update the camera
	camera->Update(deltaTime);

	// Update the gun of the player
	playerGun->Update(deltaTime);

	// Update every enemy in the list
	for (EnemyActor* enemy : enemies)
		enemy->Update(deltaTime);
}

void SceneCombination::HandleEvents(const SDL_Event& sdlEvent)
{
	// Handle events of camera
	camera->HandleEvents(sdlEvent);

	// Handle events of the player gun
	playerGun->HandleEvents(sdlEvent);

	// Handle events of every enemy
	for (EnemyActor* enemy : enemies)
		enemy->HandleEvents(sdlEvent);
}

// Basic include
#include "PlayerGun.h"

PlayerGun::PlayerGun(Vec3 offset_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActorFPS* camera_, Component* parent_) : Actor(parent_)
{
	// Set the values to the given ones
	offset = offset_;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;
	cameraFPS = camera_;
}

PlayerGun::~PlayerGun() {}

bool PlayerGun::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/PlayerGun3.obj"));
	//model_3D->SetMesh(new Mesh(nullptr, "meshes/PlayerGunOffset.obj"));
	model_3D->GetMesh()->OnCreate();

	gunMatrix = cameraFPS->GetCameraFPSLookAt() * MMath::translate(Vec3(0.0f, 0.0f, -1.0f));

	// Spawn position
	model_3D->SetModelMatrix(gunMatrix);

	// Create texture
	model_3D->SetTexture(new Texture());
	model_3D->GetTexture()->LoadImage("textures/Texture_Gray.png");
	model_3D->OnCreate();

	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	// Return true, so that the program can run
	return true;
}

void PlayerGun::OnDestroy()
{
	// If model_3D exists, call OnDestroy and delete
	if (model_3D)
	{
		model_3D->OnDestroy();
		delete model_3D;
	}

	// If shader exists, call OnDestroy and delete
	if (shader)
	{
		shader->OnDestroy();
		delete shader;
	}
}

void PlayerGun::Render()
{
	// Render calls
	glBindTexture(GL_TEXTURE_2D, model_3D->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, model_3D->GetModelMatrix());

	// Render the model
	model_3D->Render();

	// Render the bullets
	for (Bullet* bullet : spawnedBullets)
		bullet->Render();

	// Render call
	glBindTexture(GL_TEXTURE_2D, 0);
}

void PlayerGun::Update(float deltaTime)
{
	// Create and set the gun orientation and position
	Vec3 gunOrientation = cameraFPS->GetCameraFront();
	Vec3 gunPos = cameraFPS->GetCameraFPSPos() + gunOrientation + Vec3(0.0f, -0.5f, 0.0f);

	// Set orientation
	rotation = gunOrientation.x;
	rotationAxis = Vec3(0.0f, cameraFPS->GetCameraFront().y, 0.0f);

	// Set model matrix
	gunMatrix = MMath::translate(gunPos) * cameraFPS->GetCameraFPSLookAt() * MMath::inverse(cameraFPS->GetCameraRotationMatrix()) * MMath::translate(Vec3(0.0f, 0.0f, -0.2f));
	model_3D->SetModelMatrix(gunMatrix);

	// Set position
	position = model_3D->GetPosition();

	// Update the bullets
	for (Bullet* bullet : spawnedBullets)
		bullet->Update(deltaTime);

	// Handle the destruction of bullets
	HandleDestroyBullet();
}

void PlayerGun::HandleEvents(const SDL_Event& sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		// Left mouse button is down
		if (SDL_BUTTON_LEFT == sdlEvent.button.button)
			SpawnBullet(Vec3(0.0f, 0.0f, 0.0f));
	}
}

void PlayerGun::SpawnBullet(Vec3 velocity_)
{
	Vec3 offset = Vec3(0.0f, 0.1f, 0.0f);												// Spawn bullet with offset from gun
	Bullet* bullet = new Bullet(bulletLabel, position + offset, velocity_, this, this);	// Create bullet
	bulletLabel++;																		// Increase number for next bullet

	bullet->OnCreate();					// Call OnCreate for bullet
	spawnedBullets.push_back(bullet);	// Add bullet to list
}

void PlayerGun::HandleDestroyBullet()
{
	// Check if the bullet needs to be destroyed
	// If so, remove from the list and call OnDestroy for that bullet
	if (spawnedBullets.empty() == false)
	{
		for (int i = spawnedBullets.size() - 1; i >= 0; i--)
		{
			if (spawnedBullets.at(i)->GetBulletDestroyIsCalled())
			{
				cout << "Bullet " << spawnedBullets[i] << " is being destroyed in the PlayerGun!" << endl;

				Bullet* bullet = spawnedBullets[i];

				spawnedBullets[i]->OnDestroy();
				spawnedBullets.erase(spawnedBullets.begin() + i);

				delete(bullet);
			}
		}
	}
}

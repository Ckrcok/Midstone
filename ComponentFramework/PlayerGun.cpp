#include "PlayerGun.h"

PlayerGun::PlayerGun(Vec3 offset_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActorFPS* camera_, Component* parent_) : Actor(parent_)
{
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

	model_3D->SetModelMatrix(MMath::translate(cameraFPS->GetCameraFPSPos() + Vec3(0.0f, 0.0f, 0.0f)));	// Spawn position

	// Only rotate if a rotation value is given
	//if (rotation > 0)
	//	model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::rotate(rotation, rotationAxis));	// Spawn rotation

	// Create texture
	model_3D->SetTexture(new Texture());
	model_3D->GetTexture()->LoadImage("textures/Texture_Gray.png");
	model_3D->OnCreate();

	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	return true;
}

void PlayerGun::OnDestroy()
{
	if (model_3D)
	{
		model_3D->OnDestroy();
		delete model_3D;
	}

	if (shader)
	{
		shader->OnDestroy();
		delete shader;
	}
}

void PlayerGun::Render()
{
	glBindTexture(GL_TEXTURE_2D, model_3D->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, model_3D->GetModelMatrix());
	model_3D->Render();

	// Render the bullets
	for (Bullet* bullet : spawnedBullets)
		bullet->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void PlayerGun::Update(float deltaTime)
{
	// Position with correct camera position matrix
	//Vec3 posWithOffset = Vec3(-camera->cameraPositionTracker.x, camera->cameraPositionTracker.y, -camera->cameraPositionTracker.z) + offset;

	//Vec3 gunPos = cameraFPS->GetCameraFPSPos() + Vec3(0.0f, 0.0f, 0.0f);

	// Set the model matrix and the position value
	//model_3D->SetModelMatrix(MMath::translate(posWithOffset) * MMath::rotate(-camera->cameraRotationTracker.y, (const Vec3(0.0f, 1.0f, 0.0f))));
	//model_3D->SetModelMatrix(MMath::translate(gunPos));
	//model_3D->SetModelMatrix(MMath::rotate(90, Vec3 (0.0f, 1.0f, 0.0f))
								//* MMath::translate(cameraFPS->GetCameraFPSPos()));

	Vec3 gunOrientation = cameraFPS->GetCameraFPSOrientation();
	Vec3 gunPos = cameraFPS->GetCameraFPSPos() + cameraFPS->GetCameraFPSOrientation();
	model_3D->SetModelMatrix(MMath::translate(gunPos) * MMath::rotate(gunOrientation.y, Vec3(0.0f, 1.0f, 0.0f)) * MMath::translate(Vec3(0.0f, 0.0f, 0.0f)) * MMath::rotate(gunOrientation.y, Vec3(0.0f, 1.0f, 0.0f)));

	position = model_3D->GetPosition();

	// Update the bullets
	for (Bullet* bullet : spawnedBullets)
		bullet->Update(deltaTime);

	// Handle the destruction of bullets
	HandleDestroyBullet();
}

void PlayerGun::HandleEvents(const SDL_Event& sdlEvent)
{
	switch (sdlEvent.type) {
	case SDL_MOUSEBUTTONDOWN:

		// Left mouse button is down
		if (SDL_BUTTON_LEFT == sdlEvent.button.button)
			SpawnBullet(Vec3(0.0f, 0, -0.5f));
	}
}

void PlayerGun::SpawnBullet(Vec3 velocity_)
{
	Vec3 offset = Vec3(0.0f, 0.1f, -0.4f);											// Spawn bullet with offset from gun
	Bullet* bullet = new Bullet(bulletLabel, position + offset, velocity_, this);	// Create bullet
	bulletLabel++;																	// Increase number for next bullet

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

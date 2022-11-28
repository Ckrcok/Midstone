#include "PlayerGun.h"

PlayerGun::PlayerGun(Vec3 offset_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* camera_, Component* parent_) : Actor(parent_)
{
	offset = offset_;
	//if (camera->GetPlayerPosition() != nullptr)
		//position = camera->GetPlayerPosition() + offset;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;
	camera = camera_;
}

PlayerGun::~PlayerGun() {}

bool PlayerGun::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/PlayerGun3.obj"));
	model_3D->GetMesh()->OnCreate();

	model_3D->SetModelMatrix(MMath::translate(position));												// Spawn position

	if (rotation > 0)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::rotate(rotation, rotationAxis));	// Spawn rotation

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
	//position = camera->GetPlayerPosition() + offset;
	//model_3D->SetModelMatrix(MMath::translate(position));

	//cout << "Position_Cam: ";
	//camera->GetCameraActorPosition().print();

	// First rotate, then move
	// This way, the forward vector is also changed
	//model_3D->SetModelMatrix(model_3D->GetModelMatrix() * camera->GetRotationMatrix());
	//model_3D->SetModelMatrix(MMath::translate(camera->GetPlayerPosition() + offset));

	//model_3D->SetModelMatrix(MMath::rotate(-(camera->GetRotationMatrix()[10]), Vec3(0.0f, 0.0f, 1.0f)) * MMath::translate(camera->GetPlayerPosition() + offset));
	//model_3D->SetModelMatrix(camera->GetModelMatrix() * MMath::translate(camera->GetPlayerPosition() + offset));
	//model_3D->SetModelMatrix(camera->GetModelMatrix() * MMath::rotate(camera->GetRotationMatrix()));

	//model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(camera->cameraPositionTracker + offset));
	//model_3D->SetModelMatrix(MMath::rotate(-camera->cameraRotationTracker.y, (const Vec3(0.0f, 1.0f, 0.0f))));
	//model_3D->SetModelMatrix(MMath::translate(-camera->cameraPositionTracker + offset));

	//model_3D->SetModelMatrix(MMath::rotate(-camera->cameraRotationTracker.y, (const Vec3(0.0f, 1.0f, 0.0f))) * MMath::translate(-camera->cameraPositionTracker + offset));
	model_3D->SetModelMatrix(MMath::translate(-camera->cameraPositionTracker + offset) * MMath::rotate(-camera->cameraRotationTracker.y, (const Vec3(0.0f, 1.0f, 0.0f))));

	//std::cout << "Camera rotation matrix: " << camera->GetRotationMatrix()[10] << std::endl;
	std::cout << "Camera position tracker: ";
	camera->cameraPositionTracker.print();

	std::cout << "Camera rotation tracker: ";
	camera->cameraRotationTracker.print();

	std::cout << "Gun model matrix:\n";
	model_3D->GetModelMatrix().print();

	// Update the bullets
	for (Bullet* bullet : spawnedBullets)
		bullet->Update(deltaTime);
}

void PlayerGun::HandleEvents(const SDL_Event& sdlEvent)
{
	switch (sdlEvent.type) {
	case SDL_MOUSEBUTTONDOWN:

		// Left mouse button is down
		if (SDL_BUTTON_LEFT == sdlEvent.button.button) {
			//cout << "Left mouse button is down!" << endl;
			SpawnBullet(Vec3(0.0f, 0, -0.5f));
		}
	}
}

void PlayerGun::SpawnBullet(Vec3 velocity_)
{
	Vec3 offset = Vec3(0.0f, 0.1f, -0.4f);
	//Bullet* bullet = new Bullet(bulletLabel, position + offset, velocity_, this, this);
	Bullet* bullet = new Bullet(bulletLabel, position + offset, velocity_, this);
	bulletLabel++;

	bullet->OnCreate();
	spawnedBullets.push_back(bullet);
}

void PlayerGun::DestroyBullet(int label)
{
	for (int i = 0; i < spawnedBullets.size(); i++)
	{
		if (spawnedBullets[i]->GetLabel() == label) {
			spawnedBullets[i]->OnDestroy();

			spawnedBullets.erase(std::next(spawnedBullets.begin() + i - 1));
			return;
		}
	}
}

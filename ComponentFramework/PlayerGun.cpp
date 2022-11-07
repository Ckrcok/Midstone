#include "PlayerGun.h"

PlayerGun::PlayerGun(Vec3 offset_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* camera_, Component* parent_) : Actor(parent_)
{
	offset = offset_;
	position = offset;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;
	camera = camera_;
}

PlayerGun::~PlayerGun() {}

bool PlayerGun::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/PlayerGun.obj"));
	model_3D->GetMesh()->OnCreate();

	model_3D->SetModelMatrix(MMath::translate(position));											// Spawn position
	model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::rotate(rotation, rotationAxis));	// Spawn rotation

	// Create texture
	model_3D->SetTexture(new Texture());
	model_3D->GetTexture()->LoadImage("textures/ZombieTexture.png");
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

	glBindTexture(GL_TEXTURE_2D, 0);
}

void PlayerGun::Update(float deltaTime)
{
	position = camera->GetPlayerPosition() + offset;
	model_3D->SetModelMatrix(MMath::translate(position));											// Spawn position
}

void PlayerGun::HandleEvents(const SDL_Event& sdlEvent) {}

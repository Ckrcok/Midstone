#include "Bullet.h"

Bullet::Bullet(Vec3 spawnPos, Vec3 velocity_, Component* parent_) : Actor(parent_)
{
	position = spawnPos;
	velocity = velocity_;
}

Bullet::~Bullet() {}

bool Bullet::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/GunBullet.obj"));
	model_3D->GetMesh()->OnCreate();

	model_3D->SetModelMatrix(MMath::translate(position));	// Spawn position

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

void Bullet::OnDestroy()
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

void Bullet::Render()
{
	glBindTexture(GL_TEXTURE_2D, model_3D->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, model_3D->GetModelMatrix());
	model_3D->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Bullet::Update(float deltaTime)
{
	position = model_3D->GetPosition() + velocity;
	model_3D->SetModelMatrix(MMath::translate(position));
}

void Bullet::OnCollision()
{
	// [TODO]: Add collision check with the enemy
	OnDestroy();
}

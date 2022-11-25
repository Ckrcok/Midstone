#include "Bullet.h"

//Bullet::Bullet(int label_, Vec3 spawnPos, Vec3 velocity_, PlayerGun* playerGun_, Component* parent_) : Actor(parent_)
Bullet::Bullet(int label_, Vec3 spawnPos, Vec3 velocity_, Component* parent_) : Actor(parent_)
{
	label = label_;

	position = spawnPos;
	velocity = velocity_;

	//playerGun = playerGun_;

	timer = destroyAfterSeconds;
}

Bullet::~Bullet() {}

bool Bullet::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/GunBullet2.obj"));
	//model_3D->SetMesh(new Mesh(nullptr, "meshes/Mario.obj"));
	model_3D->GetMesh()->OnCreate();

	model_3D->SetModelMatrix(MMath::translate(position));	// Spawn position

	// Create texture
	model_3D->SetTexture(new Texture());
	model_3D->GetTexture()->LoadImage("textures/Texture_Gray.png");
	model_3D->OnCreate();

	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	std::cout << this << " is OnCreate" << std::endl;

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

	//std::cout << this << " is Render" << std::endl;
}

void Bullet::Update(float deltaTime)
{
	if (timer > 0.0f && !bulletDestroyIsCalled)
		timer -= deltaTime;
	else if (timer <= 0.0f && !bulletDestroyIsCalled)
	{
		std::cout << "Destroy is called for " << this << " bullet!" << std::endl;
		bulletDestroyIsCalled = true;
		//playerGun->DestroyBullet(label);
	}

	position = model_3D->GetPosition() + velocity;
	model_3D->SetModelMatrix(MMath::translate(position));

	//std::cout << this << " position: ";
	//position.print();

	//std::cout << this << " is Update" << std::endl;
}

void Bullet::OnCollision()
{
	// [TODO]: Add collision check with the enemy
	//OnDestroy();
}

// Basic include
#include "Bullet.h"

Bullet::Bullet(int label_, Vec3 spawnPos, Vec3 velocity_, PlayerGun* playerGun_, Component* parent_) : Actor(parent_)
{
	// Set the values to the given ones
	label = label_;

	position = spawnPos;
	velocity = velocity_;

	playerGun = playerGun_;

	timer = destroyAfterSeconds;
}

Bullet::~Bullet() {}

bool Bullet::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	model_3D->GetMesh()->OnCreate();

	// Set the position & scale
	model_3D->SetModelMatrix(playerGun->GetGunMatrix() * MMath::scale(Vec3(0.5f, 0.5f, 0.5f)));

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

void Bullet::OnDestroy()
{
	// If model exists, call OnDestroy and delete
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

void Bullet::Render()
{
	// Set the texture and uniform matrix
	glBindTexture(GL_TEXTURE_2D, model_3D->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, model_3D->GetModelMatrix());

	// Render the model
	model_3D->Render();

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Bullet::Update(float deltaTime)
{
	// Debug to show the timer
	//cout << this << " || Timer: " << timer << endl;

	// Lower the value of timer if is above zero and is not destroyed
	if (timer > 0.0f && !bulletDestroyIsCalled)
		timer -= deltaTime;
	else if (timer <= 0.0f && !bulletDestroyIsCalled)
	{
		// Debug to show that the bullet is destroyed
		cout << "Destroy is called for " << this << " bullet!" << endl;
		bulletDestroyIsCalled = true;
	}

	// Set the velocity
	velocity += Vec3(0.0f, 0.0f, -deltaTime * 1500);

	// Set the position of the bullet according to the velocity
	model_3D->SetModelMatrix(playerGun->GetGunMatrix() *= MMath::translate(velocity));
}

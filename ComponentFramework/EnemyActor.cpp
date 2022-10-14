#include "EnemyActor.h"

EnemyActor::EnemyActor(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, Component* parent_) : Actor(parent_)
{
	position = spawnPosition_;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;

	Vec3 target = Vec3(10.0f, 0.0f, 0.0f);
	targets.push_back(target);

	if (targets.size() > 0)
		currentTarget = 0;
}

EnemyActor::~EnemyActor() {}

bool EnemyActor::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/Zombie.obj"));
	model_3D->GetMesh()->OnCreate();

	model_3D->SetModelMatrix(MMath::translate(position));				// Spawn position
	model_3D->SetModelMatrix(MMath::rotate(rotation, rotationAxis));	// Spawn rotation

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

void EnemyActor::OnDestroy()
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

void EnemyActor::Render()
{
	glBindTexture(GL_TEXTURE_2D, model_3D->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, model_3D->GetModelMatrix());
	model_3D->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void EnemyActor::Update(float deltaTime)
{
	// Calculate distance between enemy and target
	float distanceToTarget = GetDistance(position, targets[currentTarget]);

	//cout << "DistanceToTarget: " << distanceToTarget << endl;

	// Check if target position is reached
	if (distanceToTarget < 0.5f && currentTarget + 1 < targets.size())
		currentTarget++;
	else
		MoveToTarget(deltaTime);

	// Calculate distance between enemy and player
	float distanceToPlayer = GetDistance(position, playerPos);

	// If player is in range, attack
	if (distanceToPlayer < 0.2)
		Attack();
}

void EnemyActor::HandleEvents(const SDL_Event& sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_KEYDOWN:
	{
		// Move
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_K)
			model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, -1.0f)));
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_I)
			model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_J)
			model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(1.0f, 0.0f, 0.0f)));
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_L)
			model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(-1.0f, 0.0f, 0.0f)));
	}
	}
}

void EnemyActor::MoveToTarget(float deltaTime)
{
	// [TODO] Implement move to target code
	// [TODO] Implement face to target code

	Vec3 targetPos = targets[currentTarget];
	Vec3 direction = targetPos - position;

	cout << "TargetPos: " << targetPos.x << " || " << targetPos.y << " || " << targetPos.z << "   |||   "
		<< "Direction: " << direction.x << " || " << direction.y << " || " << direction.z << endl;

	float stepAmount = 0.1f;

	// Move to the right
	if (direction.x > 0 && position.x < targetPos.x)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(stepAmount, 0.0f, 0.0f)));
	// Move to the left
	else if (direction.x < 0 && position.x > targetPos.x)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(-stepAmount, 0.0f, 0.0f)));

	// Move to the front
	if (direction.z < 0 && position.z > targetPos.z)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, -stepAmount)));
	// Move to the back
	if (direction.z > 0 && position.z < targetPos.z)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, stepAmount)));
}

float EnemyActor::GetDistance(Vec3 p, Vec3 q)
{
	// Distance = sqrt((pX-qX)^2 + (pY-qY)^2)
	return sqrt((p.x - q.x) * (p.x - q.x) +
		(p.y - q.y) * (p.y - q.y));
}

void EnemyActor::Attack()
{
	// [TODO] Implement attack code
}

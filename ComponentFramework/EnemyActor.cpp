// Basic include
#include "EnemyActor.h"

EnemyActor::EnemyActor(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActorFPS* camera_, Component* parent_) : Actor(parent_)
{
	// Set the given variables
	position = spawnPosition_;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;
	camera = camera_;

	// Set the targets
	Vec3 target = Vec3(10.0f, 0.0f, 10.0f);
	Vec3 target2 = Vec3(0, 0, 0);
	targets.push_back(target);
	targets.push_back(target2);

	// Set the current target
	if (targets.size() > 0)
		currentTarget = 0;

	// Set stunned to false
	isStunned = false;
}

EnemyActor::~EnemyActor() {}

bool EnemyActor::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	model_3D->GetMesh()->OnCreate();

	model_3D->SetModelMatrix(MMath::translate(position));											// Spawn position
	model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::rotate(rotation, rotationAxis));	// Spawn rotation

	// Create texture
	model_3D->SetTexture(new Texture());
	model_3D->GetTexture()->LoadImage("textures/Texture_Gray.png");
	model_3D->OnCreate();

	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	// Return true, so the program can run
	return true;
}

void EnemyActor::OnDestroy()
{
	// If the model exists, call OnDestroy and delete
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

void EnemyActor::Render()
{
	// Set the texture and uniform matrix
	glBindTexture(GL_TEXTURE_2D, model_3D->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, model_3D->GetModelMatrix());

	// Render the model
	model_3D->Render();

	// Bind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}

void EnemyActor::Update(float deltaTime)
{
	position = model_3D->GetPosition();

	// Calculate distance between enemy and player
	float distanceToPlayer = GetDistance(position, camera->GetCameraFPSPos());

	// Handle stun
	if (isStunned)
	{
		// Handle timer
		if (currentStunTimer > 0)
			currentStunTimer -= deltaTime;
		else
			isStunned = false;

		// Debug
		cout << "CurrentStunTimer: " << currentStunTimer << endl;

		return;
	}

	MoveToTarget(deltaTime);
	//cout << "DistanceToPlayer: " << distanceToPlayer << endl;
	//cout << "\n";

	/**/ // If player is in range, attack
	/*if (distanceToPlayer < 0.05f)
		AttackTarget(model_3D, 1.0f);
	else
		attackTarget = nullptr;*/
		/**/

}

void EnemyActor::HandleEvents(const SDL_Event& sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_KEYDOWN:
	{

		// Toggle stun state between true and false
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_M)
		{
			//isStunned = true;
			StunEnemy(5.0f);
			cout << "IsStunned: " << isStunned << endl;
		}

		// Toggle attack states
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_N)
			AttackTarget(model_3D, 2.0f);
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_B)
			attackTarget = nullptr;
	}
	}
}

void EnemyActor::MoveToTarget(float deltaTime)
{
	Vec3 targetPos = targets[currentTarget];
	float stepAmount = 0.1f;

	// Move to the right
	if (position.x < targetPos.x)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(-stepAmount, 0.0f, 0.0f)));
	// Move to the left
	else if (position.x > targetPos.x)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(stepAmount, 0.0f, 0.0f)));

	// Move to the back
	if (position.z < targetPos.z)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, -stepAmount)));
	// Move to the front
	else if (position.z > targetPos.z)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, stepAmount)));
}


void EnemyActor::MoveToTarget(Vec3 playerPos)
{
	Vec3 targetPos = playerPos;
	float stepAmount = 0.1f;

	// Move to the right
	if (position.x < targetPos.x)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(-stepAmount, 0.0f, 0.0f)));
	// Move to the left
	else if (position.x > targetPos.x)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(stepAmount, 0.0f, 0.0f)));

	// Move to the back
	if (position.z < targetPos.z)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, -stepAmount)));
	// Move to the front
	else if (position.z > targetPos.z)
		model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::translate(Vec3(0.0f, 0.0f, stepAmount)));
}

float EnemyActor::GetDistance(Vec3 p, Vec3 q)
{
	/**
	cout << "Enemy Pos: ";
	p.print();

	cout << "Camera Pos: ";
	q.print();
	/**/

	// Distance = sqrt((pX-qX)^2 + (pY-qY)^2)
	return sqrt((p.x - q.x) * (p.x - q.x) +
		(p.z - q.z) * (p.z - q.z));
}

void EnemyActor::Attack(float deltaTime)
{
	// Handle attack interval
	if (currentAttackValue > 0)
		currentAttackValue -= deltaTime;
	else
	{
		// [TODO] Implement attack code

		/**	// Pseudo code
		float damageAmount = 1.0f;
		currentTarget->Damage(damageAmount);
		/**/

		cout << "Attack!" << endl;

		// Set current value to original value
		currentAttackValue = attackInterval;
	}
}

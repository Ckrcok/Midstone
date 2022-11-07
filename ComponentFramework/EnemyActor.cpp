#include "EnemyActor.h"

EnemyActor::EnemyActor(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* player_, Component* parent_) : Actor(parent_)
{
	position = spawnPosition_;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;

	player = player_;

	Vec3 target = Vec3(10.0f, 0.0f, 0.0f);
	targets.push_back(target);

	if (targets.size() > 0)
		currentTarget = 0;

	isStunned = false;
}

EnemyActor::~EnemyActor() {}

bool EnemyActor::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/Zombie.obj"));
	model_3D->GetMesh()->OnCreate();

	model_3D->SetModelMatrix(MMath::translate(position));											// Spawn position
	//model_3D->SetModelMatrix(model_3D->GetModelMatrix() * MMath::rotate(rotation, rotationAxis));	// Spawn rotation

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


	// Handle attack
	if (attackTarget != nullptr)
		Attack(deltaTime);

	// Calculate distance between enemy and target
	float distanceToTarget = GetDistance(position, targets[currentTarget]);
	//cout << "DistanceToTarget: " << distanceToTarget << endl;

	// Check if target position is reached
	if (distanceToTarget < 0.5f && currentTarget + 1 < targets.size())
	{
		// Set a new target in given seconds
		if (currentTimeBetweenTargets > 0)
			currentTimeBetweenTargets -= deltaTime;
		else
		{
			currentTarget++;
			currentTimeBetweenTargets = timeBetweenTargets;
		}
	}
	else if (attackTarget == nullptr)
	{
		//MoveToTarget(deltaTime);
		FaceTarget(deltaTime);
	}

<<<<<<< Updated upstream

	// Calculate distance between enemy and player
	float distanceToPlayer = GetDistance(position, playerPos);
=======
	cout << "DistanceToPlayer: " << distanceToPlayer << endl;
	cout << "\n";
>>>>>>> Stashed changes

	/** // If player is in range, attack
	if (distanceToPlayer < 0.2)
		AttackTarget(model_3D, 1.0f);
	else
		attackTarget = nullptr;
	/**/
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

<<<<<<< Updated upstream
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Z) {
			orientation = QMath::angleAxisRotation(45, Vec3(0.0f, 1.0f, 0.0f));
			model_3D->SetModelMatrix(model_3D->GetModelMatrix() * QMath::toMatrix4(orientation));
		}
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_X)
=======
		// Custom rotation
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Z)
		{
			orientation = QMath::angleAxisRotation(45, Vec3(0.0f, 1.0f, 0.0f));
			model_3D->SetModelMatrix(model_3D->GetModelMatrix() * QMath::toMatrix4(orientation));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_X)
>>>>>>> Stashed changes
		{
			orientation = QMath::angleAxisRotation(-45, Vec3(0.0f, 1.0f, 0.0f));
			model_3D->SetModelMatrix(model_3D->GetModelMatrix() * QMath::toMatrix4(orientation));
		}
	}
	}
}

void EnemyActor::MoveToTarget(float deltaTime)
{
	Vec3 targetPos = targets[currentTarget];
	Vec3 direction = targetPos - position;

	/**
	cout << "TargetPos: " << targetPos.x << " || " << targetPos.y << " || " << targetPos.z << "   |||   "
		<< "Direction: " << direction.x << " || " << direction.y << " || " << direction.z << endl;
	/**/

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

void EnemyActor::FaceTarget(float deltaTime)
{
	// [TODO] Implement face to target code
<<<<<<< Updated upstream

	/**
		Vec3 targetPos = targets[currentTarget];
	Vec3 direction = targetPos - position;

	float orientation;
	orientation = atan2(targets[currentTarget].y - position.y, position.x - targets[currentTarget].x);
	/**/

	Vec3 direction = playerPos - position;
=======

	Vec3 direction = camera->GetPlayerPosition() - position;
>>>>>>> Stashed changes

	cout << "Direction: " << endl;
	direction.print();

	float angleRadians = (VMath::dot(direction, Vec3(0, 0, 1) / (VMath::normalize(direction).x * VMath::normalize(Vec3(0, 0, 1)).z)));
	float angleDegrees = angleRadians * (180 / M_PI);
	cout << "AngleRadians: " << angleRadians << endl;

<<<<<<< Updated upstream
	//Vec3 multiplication = Vec3((direction.x * 0), (direction.y * 0), (direction.z * 1));

	//float angleRadians = (direction * Vec3(0, 0, 1)) / VMath::normalize(direction);

	//float dot = VMath::dot(direction, );

	if (t < 1.1f)
	{
		Quaternion finalOrientation = QMath::angleAxisRotation(angleDegrees, Vec3(0, 1, 0));
		orientation = QMath::slerp(initialOrientation, finalOrientation, t);
		orientation = orientation * (1.0f / QMath::magnitude(orientation));

		Matrix4 identityMatrix;
		model_3D->SetModelMatrix(identityMatrix * QMath::toMatrix4(orientation));

		cout << "Orientation: " << endl;
		orientation.print();

=======
	if (t < 1.1f)
	{
		Quaternion finalOrientation = QMath::angleAxisRotation(angleDegrees, Vec3(0, 1, 0));
		orientation = QMath::slerp(initialOrientation, finalOrientation, t);
		orientation = orientation * (1.0f / QMath::magnitude(orientation));

		Matrix4 identityMatrix;
		model_3D->SetModelMatrix(identityMatrix * QMath::toMatrix4(orientation));

		cout << "Orientation: " << endl;
		orientation.print();

>>>>>>> Stashed changes
		t += 0.1f;
	}
}

float EnemyActor::GetDistance(Vec3 p, Vec3 q)
{
	// Distance = sqrt((pX-qX)^2 + (pY-qY)^2)
	return sqrt((p.x - q.x) * (p.x - q.x) +
		(p.y - q.y) * (p.y - q.y));
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

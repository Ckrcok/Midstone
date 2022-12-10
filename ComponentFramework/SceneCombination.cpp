// Basic include
#include "SceneCombination.h"

SceneCombination::SceneCombination()
{
	// Debug information
	Debug::Info("Created SceneCombination: ", __FILE__, __LINE__);
	EnemyActor* enemyA = new EnemyActor(Vec3(-17.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyB = new EnemyActor(Vec3(-2.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyC = new EnemyActor(Vec3(8.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyD = new EnemyActor(Vec3(10.0f, 0.0f, -6.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyE = new EnemyActor(Vec3(15.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);
	EnemyActor* enemyF = new EnemyActor(Vec3(16.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL);

	Vec3 minValueTriggerA = (Vec3(-17.0f, 0.0f, -24.0f) -	(Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerB = (Vec3(-2.0f, 0.0f, -24.0f) -	(Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerC = (Vec3(8.0f, 0.0f, -20.0f) -		(Vec3(16.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerD = (Vec3(10.0f, 0.0f, -6.0f) -		(Vec3(2.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerE = (Vec3(15.0f, 0.0f, 16.0f) -		(Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerF = (Vec3(16.0f, 0.0f, -4.0f) -		(Vec3(4.0f, 1.0f, 10.0f)));
	Vec3 maxValueTriggerA = (Vec3(-17.0f, 0.0f, -24.0f) +	(Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerB = (Vec3(-2.0f, 0.0f, -24.0f) +	(Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerC = (Vec3(8.0f, 0.0f, -20.0f) +		(Vec3(16.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerD = (Vec3(10.0f, 0.0f, -6.0f) +		(Vec3(2.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerE = (Vec3(15.0f, 0.0f, 16.0f) +		(Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerF = (Vec3(16.0f, 0.0f, -4.0f) +		(Vec3(4.0f, 1.0f, 10.0f)));
	
	Box* triggerRoomA = new Box(Vec3(-17.0f, 0.0f, -24.0f), minValueTriggerA, maxValueTriggerA, enemyA);//= Box(minCornerB, maxCornerB);
	Box* triggerRoomB = new Box(Vec3(-2.0f, 0.0f, -24.0f), minValueTriggerB, maxValueTriggerB, enemyB);//= Box(minCornerB, maxCornerB);
	Box* triggerRoomC = new Box(Vec3(8.0f, 0.0f, -20.0f), minValueTriggerC, maxValueTriggerC, enemyC);//= Box(minCornerB, maxCornerB);
	Box* triggerRoomD = new Box(Vec3(10.0f, 0.0f, -6.0f), minValueTriggerD, maxValueTriggerD, enemyD);//= Box(minCornerB, maxCornerB);
	Box* triggerRoomE = new Box(Vec3(15.0f, 0.0f, 16.0f), minValueTriggerE, maxValueTriggerE, enemyE);//= Box(minCornerB, maxCornerB);
	Box* triggerRoomF = new Box(Vec3(16.0f, 0.0f, -4.0f), minValueTriggerF, maxValueTriggerF, enemyF);//= Box(minCornerB, maxCornerB);

	enemiesInRooms.push_back(enemyA);
	enemiesInRooms.push_back(enemyB);
	enemiesInRooms.push_back(enemyC);
	enemiesInRooms.push_back(enemyD);
	enemiesInRooms.push_back(enemyE);
	enemiesInRooms.push_back(enemyF);

	roomTriggers.push_back(triggerRoomA);
	roomTriggers.push_back(triggerRoomB);
	roomTriggers.push_back(triggerRoomC);
	roomTriggers.push_back(triggerRoomD);
	roomTriggers.push_back(triggerRoomE);
	roomTriggers.push_back(triggerRoomF);


	
	//Wall and pickups creation
//NorthLimit
	float northWallZStart = -30.0f;
	for (int a = 0; a < 25; a++) //Until northWallZEnd
	{
		northWallZStart += 2.0f;
		Wall* wallTest;
		if (northWallZStart == -28.0f) {
		wallTest = new Wall(Vec3(20.0f, 0.0f, northWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'd');

		}
		else {
		wallTest = new Wall(Vec3(20.0f, 0.0f, northWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');

		}
		Wall* wallTestSOUTH = new Wall(Vec3(-24.0f, 0.0f, northWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		theWalls.push_back(wallTest);
		theWalls.push_back(wallTestSOUTH);
	}


	//WestLimit
	float westWallXStart = 20.0f;
	for (int a = 0; a < 22; a++) //Until northWallZEnd
	{
		westWallXStart -= 2.0f;

		Wall* wallTest = new Wall(Vec3(westWallXStart, 0.0f, -30.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');

		Wall* wallTesteast = new Wall(Vec3(westWallXStart, 0.0f, 22.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		theWalls.push_back(wallTest);
		theWalls.push_back(wallTesteast);
	}
	//A'RoomWalls  DOOR
	float AWallXStart = -30.0f;
	float AWallzStart = -8.0f;
	for (int a = 0; a < 5; a++)
	{
		AWallXStart += 2.0f;
		AWallzStart += 2.0f;
		Wall* AwallTestEast;
		Wall* AwallTestNorth = new Wall(Vec3(4.0f, 0.0f, AWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		Wall* AwallTestSouth = new Wall(Vec3(-8.0f, 0.0f, AWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		if (AWallzStart == 2.0f) {
			AwallTestEast = new Wall(Vec3(AWallzStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'a');
		}
		else {
			AwallTestEast = new Wall(Vec3(AWallzStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		}

		theWalls.push_back(AwallTestNorth);
		theWalls.push_back(AwallTestSouth);
		theWalls.push_back(AwallTestEast);
	}

	//B'RoomWalls DOOR
	float bWallXStart = -30.0f;
	for (int a = 0; a < 5; a++)
	{
		Wall* BwallTestNorth;
		bWallXStart += 2.0f;
		if (bWallXStart == -28.0f) {
			BwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, bWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'b');
		}
		else {
			BwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, bWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		}
		theWalls.push_back(BwallTestNorth);
	}
	float bWallzStart = -12.0f;
	for (int a = 0; a < 1; a++)
	{
		bWallzStart -= 2.0f;
		Wall* BwallTest = new Wall(Vec3(bWallzStart, 0.0f, -10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		Wall* BwallTestN = new Wall(Vec3(bWallzStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		theWalls.push_back(BwallTest);
		theWalls.push_back(BwallTestN);
	}
	float bWallxzStart = -18.0f;
	for (int a = 0; a < 3; a++)
	{
		bWallxzStart += 2.0f;
		Wall* BwalzlTest = new Wall(Vec3(-16.0f, 0.0f, bWallxzStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		theWalls.push_back(BwalzlTest);
	}
	//SecurityRoomDoor
	float sWallxzStart = -12.0f;
	Wall* SwalzlTest;
	for (int a = 0; a < 5; a++)
	{
		sWallxzStart -= 2.0f;
		if (sWallxzStart == -14.0f) {
			SwalzlTest = new Wall(Vec3(sWallxzStart, 0.0f, 0.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 's');
		}
		else {
			SwalzlTest = new Wall(Vec3(sWallxzStart, 0.0f, 0.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');

		}
		theWalls.push_back(SwalzlTest);
	}

	//PowerRoomDoor
	float pWallxzStart = -12.0f;
	for (int a = 0; a < 5; a++)
	{
		Wall* PwalzlTest;
		pWallxzStart -= 2.0f;
		PwalzlTest = new Wall(Vec3(pWallxzStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');


		theWalls.push_back(PwalzlTest);
	}

	//ERoomWalls DOOR
	float EWallXStart = -10.0f;
	for (int a = 0; a < 15; a++)
	{
		EWallXStart += 2.0f;
		Wall* EwallTestNorth;
		if (EWallXStart == 12.0f) {
			EwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, EWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'g');
		}
		else {
			EwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, EWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');

		}
		theWalls.push_back(EwallTestNorth);
	}


	//DRoom DOORS
	float DWallZStart = -10.0f;
	for (int a = 0; a < 9; a++) //Until northWallZEnd
	{
		DWallZStart += 2.0f;
		Wall* DwallTest;
		Wall* DwallTestSOUTH;
		
			DwallTest = new Wall(Vec3(8.0f, 0.0f, DWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		

		if (DWallZStart == -6.0f) {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, DWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'D');
		}
		else {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, DWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');

		}

		theWalls.push_back(DwallTest);
		theWalls.push_back(DwallTestSOUTH);
	}
	//DroomEASTWEST
	float DWallXStart = 8.0f;
	for (int a = 0; a < 7; a++)
	{
		DWallXStart -= 2.0f;
		Wall* DwallTest = new Wall(Vec3(DWallXStart, 0.0f, -10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		Wall* DwallTesteast = new Wall(Vec3(DWallXStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		theWalls.push_back(DwallTest);
		theWalls.push_back(DwallTesteast);
	}

	//FRoom door
	float FWallZStart = 14.0f;
	for (int a = 0; a < 3; a++)
	{

		FWallZStart += 2.0f;
		Wall* DwallTestSOUTH;
		Wall* DwallTest = new Wall(Vec3(8.0f, 0.0f, FWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		if (FWallZStart == 20.0f) {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, FWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'f');

		}
		else {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, FWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');

		}
		theWalls.push_back(DwallTest);
		theWalls.push_back(DwallTestSOUTH);
	}
	//Froom
	float FWallXStart = 8.0f;
	for (int a = 0; a < 7; a++) //Until northWallZEnd
	{
		FWallXStart -= 2.0f;
		Wall* FwallTest = new Wall(Vec3(FWallXStart, 0.0f, 14.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		theWalls.push_back(FwallTest);
	}

	//CRoom
	float CWallZStart = 20.0f;
	for (int a = 0; a < 3; a++) //Until northWallZEnd
	{
		CWallZStart -= 2.0f;
		Wall* CwallTest = new Wall(Vec3(CWallZStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');
		Wall* CwallTestSOUTH;
		if (CWallZStart == 18.0f) {
			CwallTestSOUTH = new Wall(Vec3(CWallZStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'c');
		}
		else {
			CwallTestSOUTH = new Wall(Vec3(CWallZStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');

		}
		theWalls.push_back(CwallTest);
		theWalls.push_back(CwallTestSOUTH);
	}
	//Croom
	float CWallXStart = -18.0f;
	for (int a = 0; a < 13; a++)
	{
		CWallXStart += 2.0f;
		Wall* CwallTest;

		CwallTest = new Wall(Vec3(12.0f, 0.0f, CWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'w');



		theWalls.push_back(CwallTest);
	}


	//PICKUPS
	//weapon pickup
	Wall* wpPickup = new Wall(Vec3(6.0f, 0.0f, 16.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'o');
	//health pickup
	Wall* hpPickup = new Wall(Vec3(-6.0f, 0.0f, -28.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'h');
	//key pickup
	Wall* kpPickup = new Wall(Vec3(-18.0f, 0.0f, 8.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'k');

	theWalls.push_back(wpPickup);
	theWalls.push_back(hpPickup);
	theWalls.push_back(kpPickup);

	Wall* firstInstruction = new Wall(Vec3(7.0f, 0.0f, 0.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'x');
	//health pickup
	Wall* secondInstruction = new Wall(Vec3(0.0f, 0.0f, 21.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'y');
	//key pickup
	Wall* thirdInstruction = new Wall(Vec3(-13.0f, 0.0f, 8.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), cameraFPS, NULL, 'z');

	theWalls.push_back(firstInstruction);
	theWalls.push_back(secondInstruction);
	theWalls.push_back(thirdInstruction);
}

SceneCombination::~SceneCombination()
{
	// Debug information
	Debug::Info("Deleted SceneÇombination: ", __FILE__, __LINE__);
}

bool SceneCombination::OnCreate()
{
	// Debug information
	Debug::Info("Loading assets SceneCombination: ", __FILE__, __LINE__);

	// Create camera and call OnCreate
	/*camera = new CameraActor(Vec3(0.0f, 0.0f, -10.0f), nullptr);
	camera->OnCreate();*/

	cameraFPS = new CameraActorFPS(nullptr);
	cameraFPS->OnCreate();

	// Create the player gun and call OnCreate
	playerGun = new PlayerGun(Vec3(1.0f, -0.5f, 8.0f), 0.0f, Vec3(0, 0, 0), cameraFPS, nullptr);
	playerGun->OnCreate();

	for (Wall* wall : theWalls) {
		wall->OnCreate();
	}

	for (EnemyActor* enemy : enemiesInRooms) {
		enemy->SetCamera(cameraFPS);
		enemy->OnCreate();
	}
	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)	// Debug information
		Debug::Error("Can't load shader in SceneCombination", __FILE__, __LINE__);

	// Set light positions
	lightPos[0] = Vec3(3.0f, 0.0f, -6.5f);
	lightPos[1] = Vec3(-3.0f, 0.0f, -6.5f);
	lightPos[2] = Vec3(0.0f, 3.0f, -6.5f);
	lightPos[3] = Vec3(0.0f, -3.0f, -6.5f);

	// Set diffuse values
	diffuse[0] = Vec4(0.6f, 0.0f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.0f, 0.6f, 0.0f, 0.0f);
	diffuse[2] = Vec4(0.0f, 0.0f, 0.6f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	// Set specular values
	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];

	// Return true so program can run
	return true;
}

void SceneCombination::OnDestroy()
{
	// Debug information
	Debug::Info("Deleting assets SceneCombination: ", __FILE__, __LINE__);

	// If camera exists, call OnDestroy and delete
	/*if (camera)
	{
		camera->OnDestroy();
		delete camera;
	}*/

	if (cameraFPS)
	{
		cameraFPS->OnDestroy();
		delete cameraFPS;
	}

	// If shader exists, call OnDestroy and delete
	if (shader)
	{
		shader->OnDestroy();
		delete shader;
	}

	if (playerGun)
	{
		playerGun->OnDestroy();
		delete playerGun;
	}

	for (EnemyActor* enemy : enemiesInRooms)
	{
		if (enemy)
		{
			enemy->OnDestroy();
			delete enemy;
		}
	}
	enemiesInRooms.clear();
}

void SceneCombination::Render() const
{
	// Set the culling and front face variables
	/*glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the camera
	

	// Enable depth and culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	cameraFPS->Render();

	// Set matrices
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, cameraFPS->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, cameraFPS->GetViewMatrix());

	// Set uniforms
	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);

	// Render the gun of the player
	if (hasWeapon) {
	playerGun->Render();

	}


	for (Wall* wall : theWalls) {
		wall->Render();
	}

	for (EnemyActor* enemy : enemiesInRooms) {
		enemy->Render();
	}

	// Use program 0
	glUseProgram(0);
}

void SceneCombination::Update(const float deltaTime)
{
	// Update the camera
	cameraFPS->Update(deltaTime);
	// Update the gun of the player
	playerGun->Update(deltaTime);
	//Player collider values update
	resultPlayer = cameraFPS->GetCameraFPSPos();
	minCornerPlayer = resultPlayer - Vec3(1.0f, 1.0f, 1.0f);
	maxCornerPlayer = resultPlayer + Vec3(1.0f, 1.0f, 1.0f);
	playerColliderBox->updateVertPos(resultPlayer, minCornerPlayer, maxCornerPlayer);

	//PlayerDangerRoomCollision
	for (Box* roomTriggerBox : roomTriggers) {
		//Check if the player has triggered/collided with room box

		int playerTriggerCollision = Collision::distancePointBox(resultPlayer, *roomTriggerBox);

		if (playerTriggerCollision == true) {
			cout << "---Collided with enemy trigger area" << endl;
			//get enemy closer to player																						//enemy speed
			roomTriggerBox->enemyRoom->Update(deltaTime);


			Vec3 enemyPositionOnRoom = roomTriggerBox->enemyRoom->getPositionEnemy();
			minCornerEnemy = enemyPositionOnRoom - Vec3(1.0f, 1.0f, 1.0f);
			maxCornerEnemy = enemyPositionOnRoom + Vec3(1.0f, 1.0f, 1.0f);
			enemyColliderBox->updateVertPos(enemyPositionOnRoom, minCornerEnemy, maxCornerEnemy);

			int playerEnemyCollision = Collision::distancePointBox(resultPlayer, *enemyColliderBox);
			if (playerEnemyCollision == true)
			{
				cout << "++++Collided with enemy" << endl;
				//Player cas collided with tenemy
				if (playerHealth >= 10) {
				playerHealth -= roomTriggerBox->enemyRoom->enemyDamage;
				cout << "Player is taking damage" << endl;
				}
				else {
					cout << "Player has lost all his health" << endl;
					gameOver = true;
					gameLost = true;
				}
			}
		}
		else {
			//enemy is static or returns to enemy
			roomTriggerBox->enemyRoom->setPositionEnemy(roomTriggerBox->enemyRoom->originalPos);

		}
	}
	//PlayerLevelCollision
	for (Wall* objectToTest : theWalls) {
		//objectToTest->positionInstructions();
		objectToTest->rotateWall(deltaTime);

		resultB = objectToTest->getPos();
		minCornerB = resultB - Vec3(1.0f, 1.0f, 1.0f);
		maxCornerB = resultB + Vec3(1.0f, 1.0f, 1.0f);

		blueBox->updateVertPos(resultB, minCornerB, maxCornerB);
		playerColliderBox->updateVertPos(resultPlayer, minCornerPlayer, maxCornerPlayer);

		int playerWallorDorCollision = Collision::distancePointBox(resultPlayer, *blueBox);
		int playerPickupCollision = Collision::TestSphereSphere(*playerColliderBox, *blueBox);

		if (playerWallorDorCollision && (objectToTest->id == 'w')) {//Test if facing wall
			printf("Collided with wall \n");
			cameraFPS->isFacingWall = true;
		}
		else if (playerWallorDorCollision && ((objectToTest->id == 'a') || (objectToTest->id == 'b') || (objectToTest->id == 's') || (objectToTest->id == 'g')
			|| (objectToTest->id == 'D') || (objectToTest->id == 'f') || (objectToTest->id == 'c'))) {//IDS OF ALL THE WALLS, IF THE ID IS EQUAL TO THIS LETTERS THEN ITS A WALL
			printf("Collided with door \n");
			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), objectToTest), theWalls.end());
			cameraFPS->isFacingWall = false;

		}
		else if (playerWallorDorCollision && (objectToTest->id == 'd')) {//THIS IS THE LOCKED DOOR
			printf("Collided with locked door \n"); //Door in 20,0,-28
			cameraFPS->isFacingWall = true;
			if (hasKey == true) {
				theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), objectToTest), theWalls.end());
				gameOver = true;
				gameWon = true;
			}

		}
		else if (playerPickupCollision && (objectToTest->id == 'o')) {//testing if collided with weapon pickup
			printf("Collided with weapon \n");
			hasWeapon = true;
			cameraFPS->isFacingWall = false;
			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), objectToTest), theWalls.end());
		}
		else if (playerPickupCollision && (objectToTest->id == 'h')) {//testing if collided with healthpack pickup
			printf("Collided with healthpack \n");
			hasHealth = true;
			cameraFPS->isFacingWall = false;
			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), objectToTest), theWalls.end());
		}
		else if (playerPickupCollision && (objectToTest->id == 'k')) {//testing if collided with key pickup
			printf("Collided with key pickup \n");
			hasKey = true;
			cameraFPS->isFacingWall = false;
			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), objectToTest), theWalls.end());

		}

		if (playerGun->spawnedBullets.size() > 0) {
			for (Bullet* bulletShot : playerGun->spawnedBullets) {
				Vec3 shotBulletPosition = bulletShot->GetPosition();
				int bulletWallCollision = Collision::distancePointBox(shotBulletPosition, *blueBox);
				//When a bullet collides with a enemy the enemy gets stunned
				if (bulletWallCollision == true) {
					playerGun->HandleDestroyBullet();

				}
			}

		}

	}

	//EnemyBulletColission
	for (EnemyActor* enemyCheck : enemiesInRooms) {

		Vec3 enemyPosition = enemyCheck->GetPosition();
		minCornerEnemy = enemyPosition - Vec3(1.0f, 1.0f, 1.0f);
		maxCornerEnemy = enemyPosition + Vec3(1.0f, 1.0f, 1.0f);
		enemyColliderBox->updateVertPos(enemyPosition, minCornerEnemy, maxCornerEnemy);


		if (playerGun->spawnedBullets.size() > 0) {
			for (Bullet* bulletShot : playerGun->spawnedBullets) {
				Vec3 shotBulletPosition = bulletShot->GetPosition();
				int bulletEnemyCollision = Collision::distancePointBox(shotBulletPosition, *enemyColliderBox);
				//When a bullet collides with a enemy the enemy gets stunned
				if (bulletEnemyCollision == true) {
					enemyCheck->StunEnemy(5.0f);
				}
			}

		}
	}
	//BulletWallCollision
	//EnemyBulletCollision

}

void SceneCombination::HandleEvents(const SDL_Event& sdlEvent)
{
	// Handle events of camera
	cameraFPS->HandleEvents(sdlEvent);

	for (EnemyActor* enemy : enemiesInRooms)
		enemy->HandleEvents(sdlEvent);

	// Handle events of the player gun
	playerGun->HandleEvents(sdlEvent);
}

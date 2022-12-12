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

	Vec3 minValueTriggerA = (Vec3(-17.0f, 0.0f, -24.0f) - (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerB = (Vec3(-2.0f, 0.0f, -24.0f) - (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerC = (Vec3(8.0f, 0.0f, -20.0f) - (Vec3(16.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerD = (Vec3(10.0f, 0.0f, -6.0f) - (Vec3(2.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerE = (Vec3(15.0f, 0.0f, 16.0f) - (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 minValueTriggerF = (Vec3(16.0f, 0.0f, -4.0f) - (Vec3(4.0f, 1.0f, 10.0f)));
	Vec3 maxValueTriggerA = (Vec3(-17.0f, 0.0f, -24.0f) + (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerB = (Vec3(-2.0f, 0.0f, -24.0f) + (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerC = (Vec3(8.0f, 0.0f, -20.0f) + (Vec3(16.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerD = (Vec3(10.0f, 0.0f, -6.0f) + (Vec3(2.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerE = (Vec3(15.0f, 0.0f, 16.0f) + (Vec3(4.0f, 1.0f, 4.0f)));
	Vec3 maxValueTriggerF = (Vec3(16.0f, 0.0f, -4.0f) + (Vec3(4.0f, 1.0f, 10.0f)));

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

	// CREATE GROUND AND CEILING
	// 
	// XZ plane (ground)
	ground = new Actor(nullptr);
	ground->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	ground->GetMesh()->OnCreate();
	ground->SetModelMatrix(MMath::translate(Vec3(0.0f, -1.0f, 0.0f)) * MMath::scale(Vec3(50.0f, 0.05f, 50.0f)));
	ground->SetTexture(new Texture());
	ground->GetTexture()->LoadImage("textures/ground.png");
	ground->OnCreate();

	// XZ plane (ceiling)
	ceiling = new Actor(nullptr);
	ceiling->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	ceiling->GetMesh()->OnCreate();
	ceiling->SetModelMatrix(MMath::translate(Vec3(0.0f, 1.0f, 0.0f)) * MMath::scale(Vec3(50.0f, 0.05f, 50.0f)));
	ceiling->SetTexture(new Texture());
	ceiling->GetTexture()->LoadImage("textures/grey.png");
	ceiling->OnCreate();

	// LIGHTING
	lightSource0 = new Actor(nullptr);
	lightSource0->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource0->GetMesh()->OnCreate();
	lightSource0->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.9f, 0.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource0->SetTexture(new Texture());
	lightSource0->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource0->OnCreate();

	lightSource1 = new Actor(nullptr);
	lightSource1->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource1->GetMesh()->OnCreate();
	lightSource1->SetModelMatrix(MMath::translate(Vec3(-17.0f, 0.9f, -24.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource1->SetTexture(new Texture());
	lightSource1->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource1->OnCreate();

	lightSource2 = new Actor(nullptr);
	lightSource2->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource2->GetMesh()->OnCreate();
	lightSource2->SetModelMatrix(MMath::translate(Vec3(-2.0f, 0.9f, -24.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource2->SetTexture(new Texture());
	lightSource2->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource2->OnCreate();

	lightSource3 = new Actor(nullptr);
	lightSource3->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource3->GetMesh()->OnCreate();
	lightSource3->SetModelMatrix(MMath::translate(Vec3(8.0f, 0.9f, -20.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource3->SetTexture(new Texture());
	lightSource3->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource3->OnCreate();

	lightSource4 = new Actor(nullptr);
	lightSource4->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource4->GetMesh()->OnCreate();
	lightSource4->SetModelMatrix(MMath::translate(Vec3(10.0f, 0.9f, -6.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource4->SetTexture(new Texture());
	lightSource4->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource4->OnCreate();

	lightSource5 = new Actor(nullptr);
	lightSource5->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource5->GetMesh()->OnCreate();
	lightSource5->SetModelMatrix(MMath::translate(Vec3(15.0f, 0.9f, 16.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource5->SetTexture(new Texture());
	lightSource5->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource5->OnCreate();

	lightSource6 = new Actor(nullptr);
	lightSource6->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource6->GetMesh()->OnCreate();
	lightSource6->SetModelMatrix(MMath::translate(Vec3(16.0f, 0.9f, -4.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource6->SetTexture(new Texture());
	lightSource6->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource6->OnCreate();

	lightSource7 = new Actor(nullptr);
	lightSource7->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource7->GetMesh()->OnCreate();
	lightSource7->SetModelMatrix(MMath::translate(Vec3(6.0f, 0.9f, 16.0f)) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource7->SetTexture(new Texture());
	lightSource7->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource7->OnCreate();

	lightSource8 = new Actor(nullptr);
	lightSource8->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	lightSource8->GetMesh()->OnCreate();
	lightSource8->SetModelMatrix(MMath::translate((Vec3(6.0f, 0.9f, 0.0))) * MMath::scale(Vec3(0.5f, 0.025f, 0.5f)));
	lightSource8->SetTexture(new Texture());
	lightSource8->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource8->OnCreate();


	// Set light positions
	lightPos[0] = lightSource0->GetPosition();
	lightPos[1] = lightSource1->GetPosition();
	lightPos[2] = lightSource2->GetPosition();
	lightPos[3] = lightSource3->GetPosition();
	lightPos[4] = lightSource4->GetPosition();
	lightPos[5] = lightSource5->GetPosition();
	lightPos[6] = lightSource6->GetPosition();
	lightPos[7] = lightSource7->GetPosition();
	lightPos[8] = lightSource8->GetPosition();

	// Set diffuse values
	diffuse[0] = Vec4(0.3f, 0.2f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.3f, 0.2f, 0.0f, 0.0f);
	diffuse[2] = Vec4(0.2f, 0.4f, 0.0f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.1f, 0.4f, 0.0f);
	diffuse[4] = Vec4(0.4f, 0.5f, 0.2f, 0.0f);
	diffuse[5] = Vec4(0.6f, 0.0f, 0.6f, 0.0f);
	diffuse[6] = Vec4(0.6f, 0.2f, 0.4f, 0.0f);
	diffuse[7] = Vec4(0.6f, 0.1f, 0.5f, 0.0f);
	diffuse[8] = Vec4(0.6f, 0.3f, 0.1f, 0.0f);

	// Set specular values
	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];
	specular[4] = 0.5 * diffuse[4];
	specular[5] = 0.5 * diffuse[5];
	specular[6] = 0.5 * diffuse[6];
	specular[7] = 0.5 * diffuse[7];
	specular[8] = 0.5 * diffuse[8];

	// Return true so program can run
	return true;
}

void SceneCombination::OnDestroy()
{
	// Debug information
	Debug::Info("Deleting assets SceneCombination: ", __FILE__, __LINE__);

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

	// GROUND
	if (ground)
	{
		ground->OnDestroy();
		delete ground;
	}

	// CEILING
	if (ceiling)
	{
		ceiling->OnDestroy();
		delete ceiling;
	}

	// LIGHTSOURCES
	if (lightSource0)
	{
		lightSource0->OnDestroy();
		delete lightSource0;
	}

	if (lightSource1)
	{
		lightSource1->OnDestroy();
		delete lightSource1;
	}

	if (lightSource2)
	{
		lightSource2->OnDestroy();
		delete lightSource2;
	}

	if (lightSource3)
	{
		lightSource3->OnDestroy();
		delete lightSource3;
	}

	if (lightSource4)
	{
		lightSource4->OnDestroy();
		delete lightSource4;
	}

	if (lightSource5)
	{
		lightSource5->OnDestroy();
		delete lightSource5;
	}

	if (lightSource6)
	{
		lightSource6->OnDestroy();
		delete lightSource6;
	}

	if (lightSource7)
	{
		lightSource7->OnDestroy();
		delete lightSource7;
	}

	if (lightSource8)
	{
		lightSource8->OnDestroy();
		delete lightSource8;
	}

	// ENEMIES
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
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Enable depth and culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	// Render the camera
	cameraFPS->Render();

	// Set matrices
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, cameraFPS->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, cameraFPS->GetViewMatrix());

	// Set uniforms
	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos - cameraFPS->GetCameraFPSPos());
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

	// GROUND
	glBindTexture(GL_TEXTURE_2D, ground->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, ground->GetModelMatrix());
	ground->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	// CEILING
	glBindTexture(GL_TEXTURE_2D, ceiling->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, ceiling->GetModelMatrix());
	ceiling->Render();
	glBindTexture(GL_TEXTURE_2D, 0);
		
	// LIGHT SOURCES
	glBindTexture(GL_TEXTURE_2D, lightSource0->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource0->GetModelMatrix());
	lightSource0->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource1->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource1->GetModelMatrix());
	lightSource1->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource2->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource2->GetModelMatrix());
	lightSource2->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource3->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource3->GetModelMatrix());
	lightSource3->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource4->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource4->GetModelMatrix());
	lightSource4->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource5->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource5->GetModelMatrix());
	lightSource5->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource6->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource6->GetModelMatrix());
	lightSource6->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource7->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource7->GetModelMatrix());
	lightSource7->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, lightSource8->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource8->GetModelMatrix());
	lightSource8->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

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
			resultPlayer = cameraFPS->GetCameraFPSPos();

			int playerEnemyCollision = Collision::TestSphereSphere(*playerColliderBox, *enemyColliderBox);
			if (playerEnemyCollision == true)
			{
				cout << "Collided with enemy" << endl;
				//Player cas collided with tenemy
				if (playerHealth >= 10) {
					playerHealth -= roomTriggerBox->enemyRoom->enemyDamage;
					cout << "Player is taking damage" << endl;
				}
				else {
					cout << "Player has lost all his health" << endl;
					gameOver = true;
					gameLost = true;
					cout << "GAME OVER" << endl;

				}
			}
		}
		else {
			//enemy returns to first position
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
					cout << "Bullseye!" << endl;
				}
			}

		}
	}
	
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
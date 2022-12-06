#include <glew.h>
#include <iostream>
#include <SDL.h>
//#include "Debug.h"
#include "LevelScene.h"
#include "MMath.h"
#include "Debug.h" // need to include Debug after Scene.h... why??
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "Collision.h"


LevelScene::LevelScene() :sphere(nullptr), cube(nullptr), shader(nullptr), shaderCube(nullptr) {
	Debug::Info("Created LevelScene: ", __FILE__, __LINE__);
	trackball = new Trackball();
	int spawnPos = -2.0f;
	for (int i = 0; i < 1; i++)
	{
		EnemyActor* enemy = new EnemyActor(Vec3(spawnPos, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
		spawnPos += 2;

		enemies.push_back(enemy);
	}
	char isDoor;
	//NorthLimit
	float northWallZStart = -30.0f;
	for (int a = 0; a < 25; a++) //Until northWallZEnd
	{
		northWallZStart += 2.0f;
		Wall* wallTest = new Wall(Vec3(20.0f, 0.0f, northWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		Wall* wallTestSOUTH = new Wall(Vec3(-24.0f, 0.0f, northWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		theWalls.push_back(wallTest);
		theWalls.push_back(wallTestSOUTH);
	}


	//WestLimit
	float westWallXStart = 20.0f;
	for (int a = 0; a < 22; a++) //Until northWallZEnd
	{
		westWallXStart -= 2.0f;
		Wall* wallTest = new Wall(Vec3(westWallXStart, 0.0f, -30.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		Wall* wallTesteast = new Wall(Vec3(westWallXStart, 0.0f, 22.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
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
		Wall* AwallTestNorth = new Wall(Vec3(4.0f, 0.0f, AWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		Wall* AwallTestSouth = new Wall(Vec3(-8.0f, 0.0f, AWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		if (AWallzStart == 2.0f) {
			AwallTestEast = new Wall(Vec3(AWallzStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'a');
		}
		else {
			AwallTestEast = new Wall(Vec3(AWallzStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
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
			BwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, bWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'b');
		}
		else {
			BwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, bWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		}
		theWalls.push_back(BwallTestNorth);
	}
	float bWallzStart = -12.0f;
	for (int a = 0; a < 1; a++)
	{
		bWallzStart -= 2.0f;
		Wall* BwallTest = new Wall(Vec3(bWallzStart, 0.0f, -10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		Wall* BwallTestN = new Wall(Vec3(bWallzStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		theWalls.push_back(BwallTest);
		theWalls.push_back(BwallTestN);
	}
	float bWallxzStart = -18.0f;
	for (int a = 0; a < 3; a++)
	{
		bWallxzStart += 2.0f;
		Wall* BwalzlTest = new Wall(Vec3(-16.0f, 0.0f, bWallxzStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		theWalls.push_back(BwalzlTest);
	}
	//SecurityRoomDoor
	float sWallxzStart = -12.0f;
	Wall* SwalzlTest;
	for (int a = 0; a < 5; a++)
	{
		sWallxzStart -= 2.0f;
		if (sWallxzStart == -14.0f) {
			SwalzlTest = new Wall(Vec3(sWallxzStart, 0.0f, 0.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 's');
		}
		else {
			SwalzlTest = new Wall(Vec3(sWallxzStart, 0.0f, 0.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');

		}
		theWalls.push_back(SwalzlTest);
	}

	//PowerRoomDoor
	float pWallxzStart = -12.0f;
	for (int a = 0; a < 5; a++)
	{
		Wall* PwalzlTest;
		pWallxzStart -= 2.0f;
		PwalzlTest = new Wall(Vec3(pWallxzStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');


		theWalls.push_back(PwalzlTest);
	}

	//ERoomWalls DOOR
	float EWallXStart = -10.0f;
	for (int a = 0; a < 15; a++)
	{
		EWallXStart += 2.0f;
		Wall* EwallTestNorth;
		if (EWallXStart == 12.0f) {
			EwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, EWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'g');
		}
		else {
			EwallTestNorth = new Wall(Vec3(-12.0f, 0.0f, EWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');

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
		if (DWallZStart == -6.0f) {
			DwallTest = new Wall(Vec3(8.0f, 0.0f, DWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'd');
		}
		else {
			DwallTest = new Wall(Vec3(8.0f, 0.0f, DWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		}

		if (DWallZStart == -6.0f) {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, DWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'D');
		}
		else {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, DWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');

		}

		theWalls.push_back(DwallTest);
		theWalls.push_back(DwallTestSOUTH);
	}
	//DroomEASTWEST
	float DWallXStart = 8.0f;
	for (int a = 0; a < 7; a++)
	{
		DWallXStart -= 2.0f;
		Wall* DwallTest = new Wall(Vec3(DWallXStart, 0.0f, -10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		Wall* DwallTesteast = new Wall(Vec3(DWallXStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		theWalls.push_back(DwallTest);
		theWalls.push_back(DwallTesteast);
	}

	//FRoom door
	float FWallZStart = 14.0f;
	for (int a = 0; a < 3; a++)
	{

		FWallZStart += 2.0f;
		Wall* DwallTestSOUTH;
		Wall* DwallTest = new Wall(Vec3(8.0f, 0.0f, FWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		if (FWallZStart == 20.0f) {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, FWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'f');

		}
		else {
			DwallTestSOUTH = new Wall(Vec3(-8.0f, 0.0f, FWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');

		}
		theWalls.push_back(DwallTest);
		theWalls.push_back(DwallTestSOUTH);
	}
	//Froom
	float FWallXStart = 8.0f;
	for (int a = 0; a < 7; a++) //Until northWallZEnd
	{
		FWallXStart -= 2.0f;
		Wall* FwallTest = new Wall(Vec3(FWallXStart, 0.0f, 14.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		theWalls.push_back(FwallTest);
	}

	//CRoom
	float CWallZStart = 20.0f;
	for (int a = 0; a < 3; a++) //Until northWallZEnd
	{
		CWallZStart -= 2.0f;
		Wall* CwallTest = new Wall(Vec3(CWallZStart, 0.0f, -18.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');
		Wall* CwallTestSOUTH;
		if (CWallZStart == 18.0f) {
			CwallTestSOUTH = new Wall(Vec3(CWallZStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'c');
		}
		else {
			CwallTestSOUTH = new Wall(Vec3(CWallZStart, 0.0f, 10.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');

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

		CwallTest = new Wall(Vec3(12.0f, 0.0f, CWallXStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'w');



		theWalls.push_back(CwallTest);
	}
	//PICKUPS
	//weapon pickup
	Wall* wpPickup = new Wall(Vec3(6.0f, 0.0f, 16.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'o');
	//health pickup
	Wall* hpPickup = new Wall(Vec3(-6.0f, 0.0f, -28.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'h');
	//key pickup
	Wall* kpPickup = new Wall(Vec3(-18.0f, 0.0f, 8.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL, 'k');

	theWalls.push_back(wpPickup);
	theWalls.push_back(hpPickup);
	theWalls.push_back(kpPickup);


}

LevelScene::~LevelScene()
{
	Debug::Info("Deleted LevelScene: ", __FILE__, __LINE__);
	if (trackball) delete trackball;
}

bool LevelScene::OnCreate()
{

	Debug::Info("Loading assets LevelScene: ", __FILE__, __LINE__);


	camera = new CameraActor(Vec3(0.0f, 0.0f, 0.0f), nullptr);
	camera->OnCreate();
	//PlayerCollider
	sphere = new Actor(nullptr);
	sphere->SetMesh(new Mesh(nullptr, "meshes/sphere60.obj"));
	sphere->GetMesh()->OnCreate();
	sphere->SetTexture(new Texture());
	sphere->GetTexture()->LoadImage("textures/white_sphere.png");
	sphere->OnCreate();
	shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}
	sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 0.0f)));

	lightPos[0] = Vec3(3.0f, 0.0f, -6.5f);
	lightPos[1] = Vec3(-3.0f, 0.0f, -6.5f);
	lightPos[2] = Vec3(0.0f, 3.0f, -6.5f);
	lightPos[3] = Vec3(0.0f, -3.0f, -6.5f);
	diffuse[0] = Vec4(0.6f, 0.0f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.0f, 0.6f, 0.0f, 0.0f);
	diffuse[2] = Vec4(0.0f, 0.0f, 0.6f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];

	for (Wall* wall : theWalls) {
		wall->OnCreate();
	}
	playerGun = new PlayerGun(Vec3(1.0f, 0.0f, 0.0f), 0.0f, Vec3(0, 0, 0), camera, nullptr);
	playerGun->OnCreate();

	for (EnemyActor* enemy : enemies) {
		enemy->SetCamera(camera);
		enemy->OnCreate();
	}

	cube = new Actor(nullptr);
	cube->SetMesh(new Mesh(nullptr, "meshes/PlayerGun.obj"));
	cube->GetMesh()->OnCreate();
	cube->SetTexture(new Texture());
	cube->GetTexture()->LoadImage("textures/white_sphere.png");
	cube->OnCreate();

	shaderCube = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shaderCube->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}
	cube->SetModelMatrix(cube->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 0.0f)));


	return true;

}

void LevelScene::OnDestroy() {
	Debug::Info("Deleting assets Scene2: ", __FILE__, __LINE__);
	if (camera)
	{
		camera->OnDestroy();
		delete camera;
	}

	if (sphere)
	{
		sphere->OnDestroy();
		delete  sphere;
	}

	for (EnemyActor* enemy : enemies)
	{
		if (enemy)
		{
			enemy->OnDestroy();
			delete enemy;
		}
	}
	enemies.clear();
	shader->OnDestroy();
	delete shader;
	delete texture;

}
void LevelScene::HandleEvents(const SDL_Event& sdlEvent) {

	camera->HandleEvents(sdlEvent);
}

void LevelScene::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;

	sphere->SetModelMatrix(MMath::translate(-camera->cameraPositionTracker));

	//Updating player collider position.
	resultPlayer = -camera->cameraPositionTracker;

	Vec3 rotationPlayer = camera->cameraRotationTracker;
	rotationVec = camera->cameraRotationTracker;
	playerGun->Update(deltaTime);

	resultPlayer.print("Position");
	rotationPlayer.print("Rotation");

	//rotationVec.print("ROTATION TRACKER");
	for (Wall* wall : theWalls) {
		wall->rotateWall(totalTime, wall);
		resultB = wall->getPos();

		minCornerB = resultB - Vec3(1.0f, 1.0f, 1.0f);
		maxCornerB = resultB + Vec3(1.0f, 1.0f, 1.0f);

		blueBox->updateVertPos(resultB, minCornerB, maxCornerB);
		playerColliderBox->updateVertPos(resultPlayer, minCornerPlayer, maxCornerPlayer);

		int playerWallorDorCollision = Collision::distancePointBox(resultPlayer, *blueBox);
		int playerPickupCollision = Collision::TestSphereSphere(*playerColliderBox, *blueBox);

		if (playerWallorDorCollision && (wall->id == 'w')) {//Test if facing wall
			printf("Collided with wall \n");
			camera->isFacingWall = true;
		}
		else if (playerWallorDorCollision && ((wall->id == 'a') || (wall->id == 'b') || (wall->id == 's') || (wall->id == 'g')
			|| (wall->id == 'D') || (wall->id == 'f') || (wall->id == 'c'))) {//testing if colliding wall
			printf("Collided with door \n");
			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), wall), theWalls.end());
			camera->isFacingWall = false;

		}
		else if (playerWallorDorCollision && (wall->id == 'd')) {//testing of colliding with locked door
			printf("Collided with locked door \n");
			camera->isFacingWall = true;
			if (hasKey == true) {
				theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), wall), theWalls.end());
			}

		}
		else if (playerPickupCollision && (wall->id == 'o')) {//testing if collided with weapon pickup
			printf("Collided with weapon \n");
			hasWeapon = true;
			camera->isFacingWall = false;

			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), wall), theWalls.end());
		}
		else if (playerPickupCollision && (wall->id == 'h')) {//testing if collided with healthpack pickup
			printf("Collided with healthpack \n");
			hasHealth = true;
			camera->isFacingWall = false;

			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), wall), theWalls.end());
		}
		else if (playerPickupCollision && (wall->id == 'k')) {//testing if collided with key pickup
			printf("Collided with key pickup \n");
			hasKey = true;
			camera->isFacingWall = false;

			theWalls.erase(std::remove(theWalls.begin(), theWalls.end(), wall), theWalls.end());

		}


	}
}
void LevelScene::Render() const {

	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	camera->Render();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//-----------------------
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());
	//glUseProgram(0);

	//-----------------------

	for (Wall* wall : theWalls) {
		wall->Render();
	}
	for (EnemyActor* enemy : enemies) {
		enemy->Render();
	}
	if (hasWeapon == true) {
		playerGun->Render();
	}

	//-----------------------
	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);


	glBindTexture(GL_TEXTURE_2D, sphere->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	sphere->GetMesh()->Render(GL_TRIANGLES);
	//-----------------------

	glUseProgram(0);
}





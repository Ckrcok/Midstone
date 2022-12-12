#include <glew.h>
#include <iostream>
#include <SDL.h>
//#include "Debug.h"
#include "SceneCameraTest.h"
#include "MMath.h"
#include "Debug.h" // need to include Debug after Scene.h... why??
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "CameraActor.h"
#include "CameraActorFPS.h"


SceneCameraTest::SceneCameraTest() :sphere(nullptr), cube(nullptr), shader(nullptr), shaderCube(nullptr) {
	Debug::Info("Created SceneCameraTest: ", __FILE__, __LINE__);
}

SceneCameraTest::~SceneCameraTest() {
	Debug::Info("Deleted SceneCameraTest: ", __FILE__, __LINE__);
}

bool SceneCameraTest::OnCreate() {
	Debug::Info("Loading assets SceneCameraTest: ", __FILE__, __LINE__);

	/*camera = new CameraActor(nullptr);
	camera->OnCreate();*/

	// CAMERA FPS
	cameraFPS = new CameraActorFPS(nullptr);
	cameraFPS->OnCreate();

	//modelMatrix.loadIdentity();

	// Create the player gun and call OnCreate
	playerGun = new PlayerGun(Vec3(0.0f, 0.0f, 0.0f), 0.0f, Vec3(0, 0, 0), cameraFPS, nullptr);
	playerGun->SetMesh(new Mesh(nullptr, "meshes/PlayerGun3.obj"));
	playerGun->GetMesh()->OnCreate();
	playerGun->SetModelMatrix(MMath::translate(cameraFPS->GetCameraFPSPos() + Vec3(0.0f, 0.0f, -1.0f)));
	playerGun->SetTexture(new Texture());
	playerGun->GetTexture()->LoadImage("textures/Texture_Gray.png");
	playerGun->OnCreate();

	sphere = new Actor(nullptr);
	sphere->SetMesh(new Mesh(nullptr, "meshes/Message_3.obj"));
	sphere->GetMesh()->OnCreate();
	sphere->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, -10.0f)));
	sphere->SetTexture(new Texture());
	sphere->GetTexture()->LoadImage("textures/white.png");
	sphere->OnCreate();

	objNegX = new Actor(nullptr);
	objNegX->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	objNegX->GetMesh()->OnCreate();
	objNegX->SetModelMatrix(MMath::translate(Vec3(-10.0f, 0.0f, 0.0f)));
	objNegX->SetTexture(new Texture());
	objNegX->GetTexture()->LoadImage("textures/red.png");
	objNegX->OnCreate();

	objPosX = new Actor(nullptr);
	objPosX->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	objPosX->GetMesh()->OnCreate();
	objPosX->SetModelMatrix(MMath::translate(Vec3(10.0f, 0.0f, 0.0f)));
	objPosX->SetTexture(new Texture());
	objPosX->GetTexture()->LoadImage("textures/yellow.png");
	objPosX->OnCreate();

	objNegY = new Actor(nullptr);
	objNegY->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	objNegY->GetMesh()->OnCreate();
	objNegY->SetModelMatrix(MMath::translate(Vec3(0.0f, -10.0f, 0.0f)));
	objNegY->SetTexture(new Texture());
	objNegY->GetTexture()->LoadImage("textures/pink.png");
	objNegY->OnCreate();

	objPosY = new Actor(nullptr);
	objPosY->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	objPosY->GetMesh()->OnCreate();
	objPosY->SetModelMatrix(MMath::translate(Vec3(0.0f, 10.0f, 0.0f)));
	objPosY->SetTexture(new Texture());
	objPosY->GetTexture()->LoadImage("textures/blue.png");
	objPosY->OnCreate();

	objPosZ = new Actor(nullptr);
	objPosZ->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	objPosZ->GetMesh()->OnCreate();
	objPosZ->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, 10.0f)));
	objPosZ->SetTexture(new Texture());
	objPosZ->GetTexture()->LoadImage("textures/grey.png");
	objPosZ->OnCreate();

	lightSource1 = new Actor(nullptr);
	lightSource1->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	lightSource1->GetMesh()->OnCreate();
	lightSource1->SetModelMatrix(MMath::translate(Vec3(0.0f, 5.0f, 0.0f)) * MMath::scale(Vec3(1.0f, 0.2f, 4.0f)));
	lightSource1->SetTexture(new Texture());
	lightSource1->GetTexture()->LoadImage("textures/white.png");
	lightSource1->OnCreate();

	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}

	// center lights
	lightPos[0] = Vec3(3.0f, 0.0f, 0.0f);
	lightPos[1] = Vec3(-3.0f, 0.0f, 0.0f);
	lightPos[2] = Vec3(0.0f, 3.0f, 0.0f);
	lightPos[3] = Vec3(0.0f, -3.0f, 0.0f);

	// surrounding lights
	lightPos[4] = Vec3(10.0f, 4.0f, 0.0f);
	lightPos[5] = Vec3(-10.0f, 4.0f, 0.0f);
	lightPos[6] = Vec3(0.0f, 4.0f, 10.0f);
	lightPos[7] = Vec3(0.0f, 4.0f, -10.0f);

	// GAME LEVEL LIGHT SOURCE POSITIONS
	lightPos[8] = lightSource1->GetPosition();

	// diffuse values
	diffuse[0] = Vec4(0.6f, 0.0f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.0f, 0.6f, 0.0f, 0.0f);
	diffuse[2] = Vec4(0.0f, 0.0f, 0.6f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	diffuse[4] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[5] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[6] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[7] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	// GAME LEVEL LIGHT SOURCE DIFFUSE VALUES
	diffuse[8] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	// specular values
	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];

	specular[4] = 0.5 * diffuse[4];
	specular[5] = 0.5 * diffuse[5];
	specular[6] = 0.5 * diffuse[6];
	specular[7] = 0.5 * diffuse[7];

	// GAME LEVEL LIGHT SOURCE SPECULAR VALUES
	specular[8] = 0.5 * diffuse[8];

	return true;
}

void SceneCameraTest::OnDestroy() {
	Debug::Info("Deleting assets SceneCameraTest: ", __FILE__, __LINE__);

	// LEGACY CAMERA
	/*if (camera)
	{
		camera->OnDestroy();
		delete camera;
	}*/

	// CAMERA FPS
	if (cameraFPS)
	{
		cameraFPS->OnDestroy();
		delete cameraFPS;
	}

	if (sphere)
	{
		sphere->OnDestroy();
		delete sphere;
	}

	if (objNegX)
	{
		objNegX->OnDestroy();
		delete objNegX;
	}

	if (objPosX)
	{
		objPosX->OnDestroy();
		delete objPosX;
	}

	if (objNegY)
	{
		objNegY->OnDestroy();
		delete objNegY;
	}

	if (objPosY)
	{
		objPosY->OnDestroy();
		delete objPosY;
	}

	if (objPosZ)
	{
		objPosZ->OnDestroy();
		delete objPosZ;
	}

	if (playerGun)
	{
		playerGun->OnDestroy();
		delete playerGun;
	}

	if (lightSource1)
	{
		lightSource1->OnDestroy();
		delete lightSource1;
	}

	shader->OnDestroy();
	delete shader;

}
void SceneCameraTest::HandleEvents(const SDL_Event& sdlEvent) {

	//camera->HandleEvents(sdlEvent);

	// CAMERA FPS
	cameraFPS->HandleEvents(sdlEvent);

	playerGun->HandleEvents(sdlEvent);

	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		break;

	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void SceneCameraTest::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;


	playerGun->Update(deltaTime);

	//sphere->SetModelMatrix(sphere->GetModelMatrix() * MMath::translate(deltaTime * Vec3(0.0f, 0.0f, 0.0f)) * MMath::rotate(deltaTime * 50, Vec3(0.0f, 1.0f, 0.0f)));
	printf("Sphere: \t");
	sphere->GetPosition().print();
	printf("\n\n");
	printf("\n\n");
	printf("objNegX: \t");
	objNegX->GetPosition().print();
	/*printf("\n\n");
	printf("\n\n");
	printf("Camera1: \t");
	camera->GetCamPos().print();
	printf("\n\n");
	printf("\n\n");
	printf("Camera Orientation: \t");
	camera->GetCameraOrientation().print();*/


	// CAMERA FPS
	printf("\n\n");
	printf("\n\n");
	printf("CameraFPS: \t");
	cameraFPS->GetCameraFPSPos().print();
	printf("\n\n");
	printf("\n\n");
	printf("Camera Orientation: \t");
	cameraFPS->GetCameraFPSOrientation().print();

	/*printf("\n\n");
	printf("\n\n");
	printf("viewMatrix: \t");
	camera->GetViewMatrix().print();*/
	//printf("\n\n");
	//printf("P: \t");
	//camera->GetPlayerPosition().print();
	//camera->GetViewMatrix().print();
	//theWalls[0]->GetPosition().print();



}

void SceneCameraTest::Render() const {

	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// LEGACY CAMERA RENDER
	//camera->Render();		

	// FPS CAMERA RENDER
	cameraFPS->Render();

	// LEGACY CAMERA MATRIX CALLS 
	glUseProgram(shader->GetProgram());
	/*glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());*/

	// FPS CAMERA MATRIX CALLS 
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, cameraFPS->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, cameraFPS->GetViewMatrix());

	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);


	glBindTexture(GL_TEXTURE_2D, sphere->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	//glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkyBox()->GetSkyboxTextureID());
	sphere->Render();
	//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, objNegX->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, objNegX->GetModelMatrix());
	objNegX->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, objPosX->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, objPosX->GetModelMatrix());
	objPosX->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, objNegY->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, objNegY->GetModelMatrix());
	objNegY->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, objPosY->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, objPosY->GetModelMatrix());
	objPosY->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, objPosZ->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, objPosZ->GetModelMatrix());
	objPosZ->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	// PLAYER GUN
	glBindTexture(GL_TEXTURE_2D, playerGun->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, playerGun->GetModelMatrix());
	playerGun->Render();
	glBindTexture(GL_TEXTURE_2D, 0);


	glBindTexture(GL_TEXTURE_2D, lightSource1->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, lightSource1->GetModelMatrix());
	lightSource1->Render();
	glBindTexture(GL_TEXTURE_2D, 0);


	glUseProgram(0);

}





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


SceneCameraTest::SceneCameraTest() :sphere(nullptr), light(nullptr), shader(nullptr), lightCube(nullptr) {
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

	// reference object on xz
	sphere = new Actor(nullptr);
	sphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	sphere->GetMesh()->OnCreate();
	sphere->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, -10.0f)));
	sphere->SetTexture(new Texture());
	sphere->GetTexture()->LoadImage("textures/white.png");
	sphere->OnCreate();

	// XZ plane (ground)
	ground = new Actor(nullptr);
	ground->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	ground->GetMesh()->OnCreate();
	ground->SetModelMatrix(MMath::translate(Vec3(0.0f, -3.0f, 0.0f)) * MMath::scale(Vec3(50.0f, 0.05f, 50.0f)));
	ground->SetTexture(new Texture());
	ground->GetTexture()->LoadImage("textures/ground.png");
	ground->OnCreate();

	// XZ plane (ceiling)
	ceiling = new Actor(nullptr);
	ceiling->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	ceiling->GetMesh()->OnCreate();
	ceiling->SetModelMatrix(MMath::translate(Vec3(0.0f, 5.1f, 0.0f)) * MMath::scale(Vec3(50.0f, 0.05f, 50.0f)));
	ceiling->SetTexture(new Texture());
	ceiling->GetTexture()->LoadImage("textures/white.png");
	ceiling->OnCreate();

	// walls
	wallNegZ = new Actor(nullptr);
	wallNegZ->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	wallNegZ->GetMesh()->OnCreate();
	wallNegZ->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, -50.0f)) * MMath::scale(Vec3(50.0f, 5.0f, 50.0f)));
	wallNegZ->SetTexture(new Texture());
	wallNegZ->GetTexture()->LoadImage("textures/yellow.png");
	wallNegZ->OnCreate();

	wallPosZ = new Actor(nullptr);
	wallPosZ->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	wallPosZ->GetMesh()->OnCreate();
	wallPosZ->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, 50.0f)) * MMath::scale(Vec3(50.0f, 5.0f, 50.0f)));
	wallPosZ->SetTexture(new Texture());
	wallPosZ->GetTexture()->LoadImage("textures/yellow.png");
	wallPosZ->OnCreate();

	wallNegX = new Actor(nullptr);
	wallNegX->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	wallNegX->GetMesh()->OnCreate();
	wallNegX->SetModelMatrix(MMath::translate(Vec3(-50.0f, 0.0f, 0.0f)) * MMath::scale(Vec3(50.0f, 5.0f, 50.0f)));
	wallNegX->SetTexture(new Texture());
	wallNegX->GetTexture()->LoadImage("textures/yellow.png");
	wallNegX->OnCreate();

	wallPosX = new Actor(nullptr);
	wallPosX->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	wallPosX->GetMesh()->OnCreate();
	wallPosX->SetModelMatrix(MMath::translate(Vec3(50.0f, 0.0f, 0.0f)) * MMath::scale(Vec3(50.0f, 5.0f, 50.0f)));
	wallPosX->SetTexture(new Texture());
	wallPosX->GetTexture()->LoadImage("textures/yellow.png");
	wallPosX->OnCreate();

	// LIGHTING
	lightSource1 = new Actor(nullptr);
	lightSource1->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	lightSource1->GetMesh()->OnCreate();
	lightSource1->SetModelMatrix(MMath::translate(Vec3(0.0f, 5.0f, -20.0f)) * MMath::scale(Vec3(1.0f, 0.1f, 1.0f)));
	lightSource1->SetTexture(new Texture());
	lightSource1->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource1->OnCreate();

	lightSource2 = new Actor(nullptr);
	lightSource2->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	lightSource2->GetMesh()->OnCreate();
	lightSource2->SetModelMatrix(MMath::translate(Vec3(20.0f, 5.0f, 0.0f)) * MMath::scale(Vec3(1.0f, 0.1f, 1.0f)));
	lightSource2->SetTexture(new Texture());
	lightSource2->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource2->OnCreate();

	lightSource3 = new Actor(nullptr);
	lightSource3->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	lightSource3->GetMesh()->OnCreate();
	lightSource3->SetModelMatrix(MMath::translate(Vec3(0.0f, 5.0f, 20.0f)) * MMath::scale(Vec3(1.0f, 0.1f, 1.0f)));
	lightSource3->SetTexture(new Texture());
	lightSource3->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource3->OnCreate();

	lightSource4 = new Actor(nullptr);
	lightSource4->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	lightSource4->GetMesh()->OnCreate();
	lightSource4->SetModelMatrix(MMath::translate(Vec3(-20.0f, 5.0f, 0.0f)) * MMath::scale(Vec3(1.0f, 0.1f, 1.0f)));
	lightSource4->SetTexture(new Texture());
	lightSource4->GetTexture()->LoadImage("textures/brilliant.png");
	lightSource4->OnCreate();

	objNegX = new Actor(nullptr);
	objNegX->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	objNegX->GetMesh()->OnCreate();
	objNegX->SetModelMatrix(MMath::translate(Vec3(-10.0f, 0.0f, 0.0f)));
	objNegX->SetTexture(new Texture());
	objNegX->GetTexture()->LoadImage("textures/red.png");
	objNegX->OnCreate();

	objPosX = new Actor(nullptr);
	objPosX->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
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

	// if obj = light {}
	
	// create shader

	shader = new Shader(nullptr, "shaders/multiLightVert.glsl", "shaders/multiLightFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}

	lightCube = new Shader(nullptr, "shaders/multiLight2Vert.glsl", "shaders/multiLight2Frag.glsl");
	if (lightCube->OnCreate() == false)
	{
		Debug::Error("Can't load shaderLight", __FILE__, __LINE__);
	}

	// ceiling lights
	lightPos[0] = lightSource1->GetPosition();
	lightPos[1] = lightSource2->GetPosition();
	lightPos[2] = lightSource2->GetPosition();
	lightPos[3] = lightSource2->GetPosition();

	// surrounding lights
	/*lightPos[4] = Vec3(0.0f, 0.0f, 1000.0f);
	lightPos[5] = Vec3(0.0f, 0.0f, 1000.0f);
	lightPos[6] = Vec3(0.0f, 0.0f, 1000.0f);
	lightPos[7] = Vec3(0.0f, 0.0f, 1000.0f);*/

	// GAME LEVEL LIGHT SOURCE POSITIONS
	//lightPos[8] = Vec3(0.0f, 0.0f, 1000.0f);

	// diffuse values
	diffuse[0] = Vec4(0.6f, 0.0f, 0.0f, 0.0f);
	diffuse[1] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[2] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[3] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	/*diffuse[4] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[5] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[6] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);
	diffuse[7] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);*/

	// GAME LEVEL LIGHT SOURCE DIFFUSE VALUES
	//diffuse[8] = Vec4(0.6f, 0.6f, 0.6f, 0.0f);

	// specular values
	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];

	/*specular[4] = 0.5 * diffuse[4];
	specular[5] = 0.5 * diffuse[5];
	specular[6] = 0.5 * diffuse[6];
	specular[7] = 0.5 * diffuse[7];*/

	// GAME LEVEL LIGHT SOURCE SPECULAR VALUES
	//specular[8] = 0.5 * diffuse[8];

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

	// PLAYER GUN
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

	// WALLS
	if (wallNegX)
	{
		wallNegX->OnDestroy();
		delete wallNegX;
	}

	if (wallPosX)
	{
		wallPosX->OnDestroy();
		delete wallPosX;
	}

	if (wallNegZ)
	{
		wallNegZ->OnDestroy();
		delete wallNegZ;
	}

	if (wallPosZ)
	{
		wallPosZ->OnDestroy();
		delete wallPosZ;
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

	shader->OnDestroy();
	delete shader;

	lightCube->OnDestroy();
	delete lightCube;

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

	//cameraFPS->Update(deltaTime);

	//sphere->SetModelMatrix(sphere->GetModelMatrix() * MMath::translate(deltaTime * Vec3(0.0f, 0.0f, 0.0f)) * MMath::rotate(deltaTime * 50, Vec3(0.0f, 1.0f, 0.0f)));
	printf("\n\n");
	printf("\n\n");
	printf("Sphere: \t");
	sphere->GetPosition().print();
	printf("\n\n");
	printf("\n\n");
	printf("PlayerGun: \t");
	playerGun->GetPosition().print();



	/*printf("objNegX: \t");
	objNegX->GetPosition().print();*/
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
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// LEGACY CAMERA RENDER
	//camera->Render();		

	// FPS CAMERA RENDER
	cameraFPS->Render();

	glUseProgram(shader->GetProgram());
	cout << shader->GetProgram() << " shader is active!" << endl;


	// FPS CAMERA MATRIX CALLS 
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, cameraFPS->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, cameraFPS->GetViewMatrix());	

	glBindTexture(GL_TEXTURE_2D, sphere->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	//glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkyBox()->GetSkyboxTextureID());
	sphere->Render();
	//glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

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

		// OBJECTS
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

	// WALLS
	glBindTexture(GL_TEXTURE_2D, wallNegX->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, wallNegX->GetModelMatrix());
	wallNegX->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, wallPosX->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, wallPosX->GetModelMatrix());
	wallPosX->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, wallNegZ->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, wallNegZ->GetModelMatrix());
	wallNegZ->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, wallPosZ->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, wallPosZ->GetModelMatrix());
	wallPosZ->Render();
	glBindTexture(GL_TEXTURE_2D, 0);

	//glUseProgram(0);

	// SWITCH TO LIGHT SHADER
	glUseProgram(shader->GetProgram());
	cout << shader->GetProgram() << " light cube is active!" << endl;

	// FPS CAMERA MATRIX CALLS 
	/*glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, cameraFPS->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, cameraFPS->GetViewMatrix());*/

	

	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);

	// LIGHT SOURCES
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

	

	// CAMERA ATTACHMENT
	//glBindTexture(GL_TEXTURE_2D, cameraFPS->GetCameraAttachment()->GetTexture()->getTextureID());
	//glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, cameraFPS->GetCameraAttachment()->GetModelMatrix());
	//cameraFPS->GetCameraAttachment()->Render();
	//glBindTexture(GL_TEXTURE_2D, 0);

	/*glBindTexture(GL_TEXTURE_2D, camera->GetSkyBox()->GetSkyboxTextureID());
	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkyBox()->GetSkyboxTextureID());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	glUseProgram(0);

}





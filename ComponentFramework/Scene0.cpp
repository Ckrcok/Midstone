#include <glew.h>
#include <iostream>
#include <SDL.h>
//#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h" // need to include Debug after Scene.h... why??
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "Trackball.h"
#include "CameraActor.h"
#include "Collision.h"


Scene0::Scene0() :sphere(nullptr), cube(nullptr), shader(nullptr), shaderCube(nullptr) {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
	trackball = new Trackball();

	//NorthLimit
	float northWallZStart = -22.0f;
	for (int a = 0; a < 23;  a++) //Until northWallZEnd
	{
		northWallZStart += 2.0f;
		Wall* wallTest = new Wall(Vec3(20.0f, 0.0f, northWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
		theWalls.push_back(wallTest);
	}
	//SouthLimit
	float southWallZStart = -22.0f;
	for (int a = 0; a < 23; a++) //Until northWallZEnd
	{
		southWallZStart += 2.0f;
		Wall* wallTest = new Wall(Vec3(-24.0f, 0.0f, southWallZStart), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
		theWalls.push_back(wallTest);
	}

	//WestLimit
	float westWallXStart = -26.0f;
	for (int a = 0; a < 23; a++) //Until northWallZEnd
	{
		westWallXStart += 2.0f;
		Wall* wallTest = new Wall(Vec3(westWallXStart, 0.0f, -22.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
		theWalls.push_back(wallTest);
	}
	//EastLimit
	float eastWallXStart = -26.0f;
	for (int a = 0; a < 23; a++) //Until northWallZEnd
	{
		eastWallXStart += 2.0f;
		Wall* wallTest = new Wall(Vec3(eastWallXStart, 0.0f, 24.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
		theWalls.push_back(wallTest);
	}

	//A'RoomWalls
	float AWallXStart = -8.0f;
	for (int a = 0; a < 13; a++) //Until northWallZEnd
	{
		AWallXStart += 2.0f;
		Wall* wallTest = new Wall(Vec3(AWallXStart, 0.0f, 24.0f), 0.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
		theWalls.push_back(wallTest);
	}

	//a room
	Wall* wall_a1 = new Wall(Vec3(4.0f, 0.0f, -28.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a2 = new Wall(Vec3(4.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a3 = new Wall(Vec3(4.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a4 = new Wall(Vec3(2.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_a5 = new Wall(Vec3(-2.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_a6 = new Wall(Vec3(-6.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_a7 = new Wall(Vec3(-8.0f, 0.0f, -28.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a8 = new Wall(Vec3(-8.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_a9 = new Wall(Vec3(-8.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//b room
	Wall* wall_b0 = new Wall(Vec3(-12.0f, 0.0f, -28.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b1 = new Wall(Vec3(-12.0f, 0.0f, -24.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b2 = new Wall(Vec3(-12.0f, 0.0f, -20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b3 = new Wall(Vec3(-16.0f, 0.0f, -16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b4 = new Wall(Vec3(-16.0f, 0.0f, -12.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b5 = new Wall(Vec3(-14.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b6 = new Wall(Vec3(-14.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b7 = new Wall(Vec3(-22.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b8 = new Wall(Vec3(-22.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b9 = new Wall(Vec3(-12.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b10 = new Wall(Vec3(-12.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b11 = new Wall(Vec3(-12.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b12 = new Wall(Vec3(14.0f, 0.0f, 0.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b13 = new Wall(Vec3(18.0f, 0.0f, 0.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b14 = new Wall(Vec3(22.0f, 0.0f, 0.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b15 = new Wall(Vec3(-14.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b16 = new Wall(Vec3(-18.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b17 = new Wall(Vec3(-22.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_b18 = new Wall(Vec3(-12.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b19 = new Wall(Vec3(-12.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b20 = new Wall(Vec3(-12.0f, 0.0f, 12.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b21 = new Wall(Vec3(-12.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_b22 = new Wall(Vec3(-12.0f, 0.0f, 20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);


	//c room
	Wall* wall_c1 = new Wall(Vec3(18.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c2 = new Wall(Vec3(14.0f, 0.0f, -18.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c3 = new Wall(Vec3(18.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c4 = new Wall(Vec3(14.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_c5 = new Wall(Vec3(12.0f, 0.0f, -16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c6 = new Wall(Vec3(12.0f, 0.0f, -12.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c7 = new Wall(Vec3(12.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c8 = new Wall(Vec3(12.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c9 = new Wall(Vec3(12.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c10 = new Wall(Vec3(12.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_c11 = new Wall(Vec3(12.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//d room

	Wall* wall_d1 = new Wall(Vec3(6.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d2 = new Wall(Vec3(2.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d3 = new Wall(Vec3(-2.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d4 = new Wall(Vec3(-6.0f, 0.0f, -10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d5 = new Wall(Vec3(6.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d6 = new Wall(Vec3(2.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d7 = new Wall(Vec3(-2.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d8 = new Wall(Vec3(-6.0f, 0.0f, 10.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_d9 = new Wall(Vec3(8.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d10 = new Wall(Vec3(8.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d11 = new Wall(Vec3(8.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d12 = new Wall(Vec3(8.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d13 = new Wall(Vec3(8.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d14 = new Wall(Vec3(-8.0f, 0.0f, -8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d15 = new Wall(Vec3(-8.0f, 0.0f, -4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d16 = new Wall(Vec3(-8.0f, 0.0f, 0.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d17 = new Wall(Vec3(-8.0f, 0.0f, 4.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_d18 = new Wall(Vec3(-8.0f, 0.0f, 8.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);

	//f room

	Wall* wall_f1 = new Wall(Vec3(6.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f2 = new Wall(Vec3(2.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f3 = new Wall(Vec3(-2.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f4 = new Wall(Vec3(-6.0f, 0.0f, 14.0f), 90.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);// I
	Wall* wall_f5 = new Wall(Vec3(8.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_f6 = new Wall(Vec3(8.0f, 0.0f, 20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_f7 = new Wall(Vec3(-8.0f, 0.0f, 16.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);
	Wall* wall_f8 = new Wall(Vec3(-8.0f, 0.0f, 20.0f), 180.0f, Vec3(0.0f, 1.0f, 0.0f), camera, NULL);





}

Scene0::~Scene0()
{
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
	if (trackball) delete trackball;
}

bool Scene0::OnCreate()
{

	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);


	camera = new CameraActor(Vec3(0.0f, 0.0f, -10.0f), nullptr);
	camera->OnCreate();


	for (Wall* wall : theWalls) {
		wall->OnCreate();
	}



	shader = new Shader(nullptr, "shaders/defaultBlueVert.glsl", "shaders/defaultBlueFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}





	// this work is prior to camera actor --- it will be obselete with camera actor
	/*projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 15.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print();
	modelMatrix.loadIdentity();*/

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

	return true;

}

void Scene0::OnDestroy() {
	Debug::Info("Deleting assets Scene2: ", __FILE__, __LINE__);

	if (camera)
	{
		camera->OnDestroy();
		delete camera;
	}



	shader->OnDestroy();
	delete shader;

}
void Scene0::HandleEvents(const SDL_Event& sdlEvent) {

	camera->HandleEvents(sdlEvent);



	switch (sdlEvent.type) {
		//case SDL_KEYDOWN:
		//	if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {//LEFT
		//		//sphere->SetModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, 0.0f)));
		//		sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(1.0f, 0.0f, 0.0f)));
		//		//sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(-90, Vec3(0.0f, 0.0f, -1.0f)));

		//		//sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(-1.0f, 0.0f, 0.0f)));
		//	}
		//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {//RIGHT
		//		sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f,1.0f)));

		//	}
		//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {//UP
		//		sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::rotate(-90, Vec3(0.0f, 1.0f, 0.0f)));

		//	//sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 1.0f, 0.0f)));

		//	}
		//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {//DOWN
		//		sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(-1.0f, 0.0f, 0.0f)));

		//	}
		//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_X) {//BEHIND
		//		sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, -1.0f)));

		//	}
		//	else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) {//FRONT
		//		sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));

		//	}
		//	break;
	}
}

void Scene0::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;

	bool isTouching = false;

}

void Scene0::Render() const {

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
	//-----------------------

	for (Wall* wall : theWalls) {
		wall->Render();
	}
	glUseProgram(0);
}





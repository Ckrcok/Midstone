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
}

Scene0::~Scene0() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
	if (trackball) delete trackball;
}

bool Scene0::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);

	camera = new CameraActor(nullptr);
	camera->OnCreate();

	sphere = new Actor(nullptr);
	sphere->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	sphere->GetMesh()->OnCreate();
	sphere->SetTexture(new Texture());
	sphere->GetTexture()->LoadImage("textures/white_sphere.png");
	sphere->OnCreate();



	

	cube = new Actor(nullptr);
	cube->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	cube->GetMesh()->OnCreate();
	cube->SetTexture(new Texture());
	cube->GetTexture()->LoadImage("textures/white_sphere.png");
	cube->OnCreate();





	shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}

	shaderCube = new Shader(nullptr, "shaders/defaultBlueVert.glsl", "shaders/defaultBlueFrag.glsl");
	if (shaderCube->OnCreate() == false)
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

	if (sphere)
	{
		sphere->OnDestroy();
		delete sphere;
	}


	shader->OnDestroy();
	delete shader;

}
void Scene0::HandleEvents(const SDL_Event& sdlEvent) {

	camera->HandleEvents(sdlEvent);
	


	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_A) {//LEFT
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(-1.0f, 0.0f, 0.0f)));
		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_D) {//RIGHT
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(1.0f, 0.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) {//UP
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 1.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_S) {//DOWN
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, -1.0f, 0.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_X) {//BEHIND
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, -1.0f)));

		}
		else if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_Q) {//FRONT
			sphere->SetModelMatrix(sphere->GetModelMatrix() *= MMath::translate(Vec3(0.0f, 0.0f, 1.0f)));

		}
		break;
	}
}

void Scene0::Update(const float deltaTime) {
	static float totalTime = 0.0f;
	totalTime += deltaTime;

	bool isTouching = false;
	resultA = sphere->GetModelMatrix() * test;
	minCornerA = resultA - Vec3(1.0f, 1.0f, 1.0f);
	maxCornerA = resultA + Vec3(1.0f, 1.0f, 1.0f);

	resultB = cube->GetModelMatrix() * test;
	minCornerB = resultB - Vec3(1.0f, 1.0f, 1.0f);
	maxCornerB = resultB + Vec3(1.0f, 1.0f, 1.0f);
	redBox.updateVertPos(minCornerA, maxCornerA);
	blueBox.updateVertPos(minCornerB, maxCornerB);


	int a = Collision::boxBoxCollision(blueBox, redBox);
	printf("%i", a);
	//cube->SetModelMatrix(MMath::rotate(10 * totalTime, Vec3(0.0f, 0.0f, 1.0f))); // test if update is working


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

	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);

	glBindTexture(GL_TEXTURE_2D, sphere->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	sphere->GetMesh()->Render(GL_TRIANGLES);
	//-----------------------
	glUseProgram(shaderCube->GetProgram());
	glUniformMatrix4fv(shaderCube->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shaderCube->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());

	glUniform3fv(shaderCube->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shaderCube->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shaderCube->GetUniformID("specular[0]"), 10, *specular);

	glBindTexture(GL_TEXTURE_2D, cube->GetTexture()->getTextureID());
	glUniformMatrix4fv(shaderCube->GetUniformID("modelMatrix"), 1, GL_FALSE, cube->GetModelMatrix());
	cube->Render();

	glBindTexture(GL_TEXTURE_2D, 0);


	glUseProgram(0);
}





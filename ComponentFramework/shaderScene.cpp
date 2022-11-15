#include <glew.h>
#include <iostream>
#include <SDL.h>
//#include "Debug.h"
#include "shaderScene.h"
#include "MMath.h"
#include "Debug.h" // need to include Debug after Scene.h... why??
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"


shaderScene::shaderScene() :sphere(nullptr), mesh(nullptr), shader(nullptr), texture(nullptr) {
	Debug::Info("Created shaderScene: ", __FILE__, __LINE__);
}

shaderScene::~shaderScene() {
	Debug::Info("Deleted shaderScene: ", __FILE__, __LINE__);

}

bool shaderScene::OnCreate() {
	Debug::Info("Loading assets shaderScene: ", __FILE__, __LINE__);

	sphere = new Actor(nullptr);
	sphere->SetMesh(new Mesh(nullptr, "meshes/Sphere.obj"));
	sphere->GetMesh()->OnCreate();
	sphere->SetTexture(new Texture());
	sphere->GetTexture()->LoadImage("textures/white_sphere.png");
	sphere->OnCreate();

	shader = new Shader(nullptr, "shaders/testingFrag.glsl", "shaders/testingVert.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}

	// this work is prior to camera actor --- it will be obselete with camera actor
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 15.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	modelMatrix.loadIdentity();

	lightPos[0] = Vec3(3.0f, 0.0f, -6.5f);
	lightPos[1] = Vec3(-3.0f, 0.0f, -6.5f);
	lightPos[2] = Vec3(0.0f, 3.0f, -6.5f);
	lightPos[3] = Vec3(0.0f, -3.0f, -6.5f);

	diffuse[0] = Vec4(0.6, 0.0, 0.0, 0.0);
	diffuse[1] = Vec4(0.0, 0.6, 0.0, 0.0);
	diffuse[2] = Vec4(0.0, 0.0, 0.6, 0.0);
	diffuse[3] = Vec4(0.6, 0.6, 0.6, 0.0);

	specular[0] = 0.5 * diffuse[0];
	specular[1] = 0.5 * diffuse[1];
	specular[2] = 0.5 * diffuse[2];
	specular[3] = 0.5 * diffuse[3];

	return true;
}

void shaderScene::OnDestroy() {
	Debug::Info("Deleting assets Scene1: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;
	mesh->OnDestroy();
	delete mesh;
	shader->OnDestroy();
	delete shader;

	delete texture;
}
void shaderScene::HandleEvents(const SDL_Event& sdlEvent) {
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

void shaderScene::Update(const float deltaTime) {

}

void shaderScene::Render() const {



	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);

	glUniform3fv(shader->GetUniformID("lightPos[0]"), 10, *lightPos);
	glUniform4fv(shader->GetUniformID("diffuse[0]"), 10, *diffuse);
	glUniform4fv(shader->GetUniformID("specular[0]"), 10, *specular);

	glBindTexture(GL_TEXTURE_2D, sphere->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	sphere->Render();



	glBindTexture(GL_TEXTURE_2D, 0);


	glUseProgram(0);
}





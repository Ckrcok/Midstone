#include <glew.h>
#include <iostream>
#include <SDL.h>
//#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "Debug.h" // need to include Debug after Scene.h... why??
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"


Scene1::Scene1() :sphere(nullptr), mesh(nullptr), shader(nullptr), texture(nullptr) {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene1: ", __FILE__, __LINE__);

}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene1: ", __FILE__, __LINE__);

	sphere = new Actor(nullptr);
	sphere->OnCreate();

	mesh = new Mesh(nullptr, "meshes/Sphere.obj");
	if (mesh->OnCreate() == false)
	{
		Debug::Error("Can't load Mesh", __FILE__, __LINE__);
	}

	shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	if (shader->OnCreate() == false)
	{
		Debug::Error("Can't load shader", __FILE__, __LINE__);
	}

	texture = new Texture();
	if (texture->LoadImage("textures/white_sphere.png") == false)
	{
		Debug::Error("Can't load white_sphere texture", __FILE__, __LINE__);
	}

	// this work is prior to camera actor --- it will be obselete with camera actor
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 15.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	viewMatrix.print();
	//modelMatrix.loadIdentity();

	// lights here...

	return true;
}

void Scene1::OnDestroy() {
	Debug::Info("Deleting assets Scene1: ", __FILE__, __LINE__);
	sphere->OnDestroy();
	delete sphere;
	mesh->OnDestroy();
	delete mesh;
	shader->OnDestroy();
	delete shader;

	delete texture;
}
void Scene1::HandleEvents(const SDL_Event &sdlEvent) {
	switch( sdlEvent.type ) {
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

void Scene1::Update(const float deltaTime) {
	
}

void Scene1::Render() const {

	/*glCullFace(GL_BACK);
	glFrontFace(GL_CCW);*/

	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);

	/*glBindTexture(GL_TEXTURE_2D, camera->GetSkyBox()->GetSkyboxTextureID());
	glBindTexture(GL_TEXTURE_CUBE_MAP, camera->GetSkyBox()->GetSkyboxTextureID());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	// lights here...
	
	// end lights...

	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, modelMatrix);
	glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	mesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);


	glUseProgram(0);
}



	

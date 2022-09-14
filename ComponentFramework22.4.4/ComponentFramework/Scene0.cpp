#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "MeshComponent.h"
#include "ShaderComponent.h"
#include "MaterialComponent.h"
#include "TransformComponent.h"
#include "CameraActor.h"


Scene0::Scene0() {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);

}

bool Scene0::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);

	camera = new CameraActor(nullptr);
	camera->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, 0.0f), Quaternion());
	camera->OnCreate();
	camera->GetProjectionMatrix().print("ProjectionMatrix");
	camera->GetViewMatrix().print("ViewMatrix");

	waluigi = new Actor(nullptr);
	waluigi->AddComponent<MeshComponent>(nullptr, "meshes/Mario.obj");
	waluigi->AddComponent<ShaderComponent>(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	waluigi->AddComponent<MaterialComponent>(nullptr,"textures/mario_main.png");
	waluigi->AddComponent<TransformComponent>(nullptr, Vec3(0.0f, 0.0f, 0.0f), Quaternion());
	waluigi->OnCreate();
	waluigi->ListComponents();
	return true;
}

void Scene0::OnDestroy() {
	waluigi->RemoveAllComponents();
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);
}
void Scene0::HandleEvents(const SDL_Event &sdlEvent) {
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

void Scene0::Update(const float deltaTime) {
	
}

void Scene0::Render() const {
	glEnable(GL_DEPTH_TEST);
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ShaderComponent* shader = waluigi->GetComponent<ShaderComponent>();
	MeshComponent* mesh = waluigi->GetComponent<MeshComponent>();
	TransformComponent* transform = waluigi->GetComponent<TransformComponent>();
	MaterialComponent* texture = waluigi->GetComponent<MaterialComponent>();

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, camera->GetProjectionMatrix());
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, camera->GetViewMatrix());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, transform->GetTransformMatrix());
	mesh->Render(GL_TRIANGLES);

	glUseProgram(0);
}



	

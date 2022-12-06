#include "Wall.h"

Wall::Wall(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* camera_, Component* parent_, char id_) : Actor(parent_)
{
	position = spawnPosition_;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;
	id = id_;
}
Wall::Wall(float radius_, Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* camera_, Component* parent_, char id_) : Actor(parent_)
{
	position = spawnPosition_;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;
	id = id_;
	radius = radius_;
}

Wall::~Wall() {}

bool Wall::OnCreate()
{
	objFile = new Actor(nullptr);
	if (id == 'o' || id == 'h' || id == 'k') {
		objFile->SetMesh(new Mesh(nullptr, "meshes/sphere60.obj"));
	}
	else {
		objFile->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));

	}
	objFile->GetMesh()->OnCreate();

	//objFile->SetModelMatrix(MMath::translate(position));											// Spawn position
	objFile->SetModelMatrix(MMath::translate(position) * MMath::rotate(rotation, rotationAxis));	// Spawn rotation

	objFile->SetTexture(new Texture());
	objFile->GetTexture()->LoadImage("textures/white_sphere.png");
	objFile->OnCreate();
	if (id == 'w') {
		shader = new Shader(nullptr, "shaders/defaultBlueVert.glsl", "shaders/defaultBlueFrag.glsl");
	}else {
	shader = new Shader(nullptr, "shaders/defaultVert.glsl", "shaders/defaultFrag.glsl");
	}
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	return true;
}


void Wall::OnDestroy()
{
	if (objFile)
	{
		objFile->OnDestroy();
		delete objFile;
	}
}
void Wall::moveWall()
{
	//Sleep(1000);
	objFile->SetModelMatrix(objFile->GetModelMatrix() * MMath::translate(Vec3(1.0f, 0.0f, 0.0f)));
	//Sleep(1000);
	objFile->SetModelMatrix(objFile->GetModelMatrix() * MMath::translate(Vec3(0.0f, -10.0f, 0.0f)));
}


void Wall::Render()
{
	//glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, objFile->GetModelMatrix());
	glBindTexture(GL_TEXTURE_2D, objFile->GetTexture()->getTextureID());
	objFile->GetMesh()->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

}
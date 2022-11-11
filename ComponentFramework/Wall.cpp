#include "Wall.h"

Wall::Wall(Vec3 spawnPosition_, float spawnRotation_, Vec3 spawnRotationAxis_, CameraActor* camera_, Component* parent_) : Actor(parent_)
{
	position = spawnPosition_;
	rotation = spawnRotation_;
	rotationAxis = spawnRotationAxis_;

}


Wall::~Wall() {}

bool Wall::OnCreate()
{
	objFile = new Actor(nullptr);

	objFile->SetMesh(new Mesh(nullptr, "meshes/Cube.obj"));
	objFile->GetMesh()->OnCreate();
	objFile->SetModelMatrix(MMath::translate(position) * MMath::rotate(rotation, rotationAxis));
	//objFile->SetModelMatrix(
		//MMath::rotate(rotation, rotationAxis) * MMath::translate(position));

	objFile->GetMesh()->OnCreate();

	objFile->SetModelMatrix(MMath::translate(position));											// Spawn position
	objFile->SetModelMatrix(objFile->GetModelMatrix() * MMath::rotate(rotation, rotationAxis));	// Spawn rotation

	objFile->SetTexture(new Texture());
	objFile->GetTexture()->LoadImage("textures/white_sphere.png");
	objFile->OnCreate();

	shader = new Shader(nullptr, "shaders/defaultBlueVert.glsl", "shaders/defaultBlueFrag.glsl");
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

	if (shader)
	{
		shader->OnDestroy();
		delete shader;
	}
}

void Wall::Render()
{
	glBindTexture(GL_TEXTURE_2D, objFile->GetTexture()->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, objFile->GetModelMatrix());
<<<<<<< Updated upstream
	objFile->GetMesh()->Render(GL_TRIANGLES);

=======
	objFile->Render();
>>>>>>> Stashed changes
	glBindTexture(GL_TEXTURE_2D, 0);
}
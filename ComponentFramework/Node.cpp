#include "Node.h"

Node::~Node() {}

bool Node::OnCreate()
{
	// Create model
	model_3D = new Actor(nullptr);
	model_3D->SetMesh(new Mesh(nullptr, "meshes/sphere60.obj"));
	model_3D->GetMesh()->OnCreate();

	// Spawn position
	model_3D->SetModelMatrix(MMath::translate(position));

	// Create texture
	model_3D->SetTexture(new Texture());

	if (isAccessible)
		model_3D->GetTexture()->LoadImage("textures/Texture_Green.png");
	else
		model_3D->GetTexture()->LoadImage("textures/Texture_Red.png");

	model_3D->OnCreate();

	cout << "Loaded texture!" << endl;

	// Create shader
	shader = new Shader(nullptr, "shaders/multilightVert.glsl", "shaders/multilightFrag.glsl");
	if (shader->OnCreate() == false)
		Debug::Error("Can't load shader", __FILE__, __LINE__);

	return true;
}

void Node::OnDestroy()
{
	if (model_3D)
	{
		model_3D->OnDestroy();
		delete model_3D;
	}

	if (shader)
	{
		shader->OnDestroy();
		delete shader;
	}
}

void Node::Render()
{
	if (model_3D->GetTexture() != nullptr)
	{
		glBindTexture(GL_TEXTURE_2D, model_3D->GetTexture()->getTextureID());
		glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, model_3D->GetModelMatrix());
		model_3D->Render();

		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

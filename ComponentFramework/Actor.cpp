#include "Actor.h"

Actor::Actor(Component* parent_) :Component(parent_) {}

Actor::~Actor() {}

void Actor::ListComponents() const
{
	for (auto c : components)
		std::cout << typeid(*c).name() << std::endl;
}

bool Actor::OnCreate()
{
	if (mesh)
		mesh->OnCreate();

	return true;
}

void Actor::OnDestroy()
{
	if (mesh)
	{
		mesh->OnDestroy();
		delete mesh;
	}

	if (texture)
		delete texture;
}

void Actor::Update(const float deltaTime) {}

void Actor::Render()const
{
	mesh->Render(GL_TRIANGLES);
}

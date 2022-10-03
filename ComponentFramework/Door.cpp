#include "Door.h"

Door::Door(Vec3 spawnPosition_, float spawnRotation_)
{
	position = spawnPosition_;
	rotation = spawnRotation_;
}

Door::~Door() {}

void Door::OpenDoor()
{
	isOpen = true;

	cout << "Door is opening" << endl;

	// Open door
}

void Door::CloseDoor()
{
	isOpen = false;

	cout << "Door is closing" << endl;

	// Close door
}

#pragma region Get Functions
bool Door::GetIsOpen()
{
	return isOpen;
}
#pragma endregion

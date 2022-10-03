#ifndef DOOR_H
#define DOOR_H

#include "Vector.h"

using namespace MATH;
using namespace std;

class Door
{
private:
	Vec3 position;
	float rotation;

	bool isOpen;

public:
	Door(Vec3 spawnPosition_, float spawnRotation_);
	~Door();

	void OpenDoor();
	void CloseDoor();

	bool GetIsOpen();
};

#endif // !DOOR_H

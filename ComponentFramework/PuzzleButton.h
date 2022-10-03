#ifndef PUZZLE_BUTTON_H
#define PUZZLE_BUTTON_H

#include "Vector.h"

using namespace MATH;

class PuzzleButton
{
private:
	Vec3 position;
	float rotation;

	bool isOpen;

public:
	PuzzleButton(Vec3 spawnPosition_, float spawnRotation_);
	~PuzzleButton();

	bool GetIsOpen();

	void Open();
	void Close();
};

#endif // !PUZZLE_BUTTON_H

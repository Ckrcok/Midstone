#include "PuzzleButton.h"

PuzzleButton::PuzzleButton(Vec3 spawnPosition_, float spawnRotation_, bool isOpen_)
{
	position = spawnPosition_;
	rotation = spawnRotation_;

	isOpen = isOpen_;

	if (isOpen)
		Open();
	else
		Close();
}

PuzzleButton::~PuzzleButton() {}

void PuzzleButton::Open()
{
	isOpen = true;

	// Play open animation
}

void PuzzleButton::Close()
{
	isOpen = false;

	// Play close animation
}

bool PuzzleButton::GetIsOpen()
{
	return isOpen;
}

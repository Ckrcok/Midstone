#ifndef DOOR_PUZZLE_H
#define DOOR_PUZZLE_H

#include "PuzzleButton.h"
#include "Door.h"
#include <SDL.h>

#include <iostream>
#include <vector>

using namespace std;

class DoorPuzzle
{
private:
	//vector<PuzzleButton> buttons[2];
	PuzzleButton* buttons[3];
	Door* door;

public:
	DoorPuzzle();
	~DoorPuzzle();

	void HandleEvents(const SDL_Event& event);
	void Update();

	void CheckButtons();
	void OpenDoor();
};

#endif // !DOOR_PUZZLE_H

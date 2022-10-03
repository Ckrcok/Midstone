#include "DoorPuzzle.h"

DoorPuzzle::DoorPuzzle()
{
	cout << "DoorPuzzle function!" << endl;

	// Initialize door
	door = new Door(Vec3(0.0f, 0.0f, 0.0f), 0.0f);

	// Create three buttons and add them to the list
	for (int i = 0; i < 3; i++)
	{
		PuzzleButton* button_ = new PuzzleButton();
		buttons[i] = button_;
	}

	// Close all the locks (buttons)
	for (int i = 0; i < sizeof(buttons); i++)
		buttons[i]->Close();
}

DoorPuzzle::~DoorPuzzle() {}

void DoorPuzzle::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_W:
			if (buttons[0]->GetIsOpen())
				buttons[0]->Close();
			else
				buttons[0]->Open();

			cout << "Button 1 is open: " << buttons[0]->GetIsOpen() << endl;
			cout << "Button W is pressed" << endl;
			break;

		case SDL_SCANCODE_O:
			if (buttons[1]->GetIsOpen())
				buttons[1]->Close();
			else
				buttons[1]->Open();

			cout << "Button 2 is open: " << buttons[1]->GetIsOpen() << endl;
			break;

		case SDL_SCANCODE_P:
			if (buttons[2]->GetIsOpen())
				buttons[2]->Close();
			else
				buttons[2]->Open();

			cout << "Button 3 is open: " << buttons[2]->GetIsOpen() << endl;
			break;
		}
	}

	// Only check if the door is not already open
	if (!door->GetIsOpen())
		CheckButtons();
	else
		cout << "Puzzle door is already open" << endl;
}

void DoorPuzzle::Update()
{

}

void DoorPuzzle::CheckButtons()
{
	for (int i = 0; i < sizeof(buttons); i++)
	{
		if (!buttons[i]->GetIsOpen())
		{
			cout << "Not all buttons are open!" << endl;
			return;
		}
		else
		{
			cout << "All buttons are open!" << endl;
			OpenDoor();
		}
	}
}

void DoorPuzzle::OpenDoor()
{
	// Check if door is not already open
	if (!door->GetIsOpen())
		door->OpenDoor();
}

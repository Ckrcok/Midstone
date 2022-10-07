#include "DoorPuzzle.h"

DoorPuzzle::DoorPuzzle()
{
	// Initialize door
	door = new Door(Vec3(0.0f, 0.0f, 0.0f), 0.0f, false);

	// Create three buttons and add them to the list
	for (int i = 0; i < 3; i++)
	{
		PuzzleButton* button_ = new PuzzleButton(Vec3(0, 0, 0), 0.0f, false);
		buttons[i] = button_;
	}
}

DoorPuzzle::~DoorPuzzle() {}

void DoorPuzzle::HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch (event.key.keysym.scancode)
		{
		case SDL_SCANCODE_I:

			//Lock 1
			if (buttons[0]->GetIsOpen())
				buttons[0]->Close();
			else
				buttons[0]->Open();

			//Lock 2
			if (buttons[1]->GetIsOpen())
				buttons[1]->Close();
			else
				buttons[1]->Open();

			// Check the states of the buttons
			CheckButtons();
			break;

		case SDL_SCANCODE_O:
			// Lock 2
			if (buttons[1]->GetIsOpen())
				buttons[1]->Close();
			else
				buttons[1]->Open();

			// Check the states of the buttons
			CheckButtons();
			break;

		case SDL_SCANCODE_P:
			// Lock 2
			if (buttons[1]->GetIsOpen())
				buttons[1]->Close();
			else
				buttons[1]->Open();

			// Lock 3
			if (buttons[2]->GetIsOpen())
				buttons[2]->Close();
			else
				buttons[2]->Open();

			// Check the states of the buttons
			CheckButtons();
			break;
		}
	}
}

void DoorPuzzle::Update() {}

void DoorPuzzle::CheckButtons()
{
	// Create openDoor bool and set to true
	bool openDoor = true;

	// Check for all the buttons if it is closed
	// If so, set bool to false and return
	for (int i = 0; i < 3; i++)
	{
		if (!buttons[i]->GetIsOpen())
		{
			openDoor = false;
			cout << "Button " << i + 1 << " is closed!" << endl;
			return;
		}
	}

	// Check if door needs to be opened
	if (openDoor)
		OpenDoor();
}

void DoorPuzzle::OpenDoor()
{
	// Check if door is not already open
	if (!door->GetIsOpen())
	{
		door->OpenDoor();
		cout << "Door is opened!" << endl;
	}
}

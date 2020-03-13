#pragma once

#include "SDL.h"
#include "variables.h"

// This is a delegated sub-system in-charge of user input control
class InputSystem {

protected:

	bool go_on = true;	// When user wants to stop --> this becomes false
	KeyStatus keys;		// All bindings

public:

	// Update 'keys'
	void update();

	// Returns the keyboard status. If a flag is set, the corresponding key is being held down.
	void getKeyStatus(KeyStatus* keys);

	// Get go_on
	bool getGoOn();
};
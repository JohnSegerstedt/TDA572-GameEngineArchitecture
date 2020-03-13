#pragma once

#ifndef __AVANCEZ_LIB__
#define __AVANCEZ_LIB__

#include "SDL.h"
#include "SDL_ttf.h"
#include "variables.h"
#include "input_system.h"
#include "text_system.h"
#include "graphics_system.h"

class AvancezLib {

public:

	unsigned int* level;

	// Destroys the avancez library instance
	void destroy();

	// Creates the main window. Returns true on success.
	bool init(int width, int height);

	// Clears the screen and draws all sprites and texts which have been drawn
	// since the last update call.
	// If update returns false, the application should terminate.
	bool update();

	void terminate();



	// Draws the given text - a delegated method for the TextSystem
	void drawText(int x, int y, const char* msg);

	// Returns the keyboard status. If a flag is set, the corresponding key is being held down. - a delegated method for the InputSystem
	void getKeyStatus(KeyStatus* keys);

private:
	SDL_Window * window;
	SDL_Renderer * renderer;

	// SUB-ENGINES
	InputSystem input_engine;
	TextSystem text_engine;

	// All different level backgrounds, currently: {day, night}
	Sprite* backgrounds[NUM_BACKGROUNDS];


	bool go_on;
};





#endif // __AVANCEZ_LIB__

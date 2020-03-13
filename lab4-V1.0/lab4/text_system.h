#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

// This is a delegated sub-system responsible for text rendering on the screen
class TextSystem{

private:
	TTF_Font* font;				// The font
	SDL_Renderer * renderer;	// The renderer

public:
	void drawText(int x, int y, const char* msg);	// Draw text on screen
	void setRenderer(SDL_Renderer* renderer);		// Give renderer
	void setFont(TTF_Font* font);					// Give Font
	void destroyFont(); // Garbage collection is important in c++
};
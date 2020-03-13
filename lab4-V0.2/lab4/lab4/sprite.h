#pragma once

#include "SDL.h"

class Sprite {
	SDL_Renderer * renderer;
	SDL_Texture * texture;
	int width;

public:

	Sprite(SDL_Renderer * renderer, SDL_Texture * texture, int width);

	// Destroys the sprite instance
	void destroy();

	// Draw the sprite at the given position.
	// Valid coordinates are between (0,0) (upper left) and (width-32, height-32) (lower right).
	// (All sprites are 32*32 pixels, clipping is not supported)
	void draw(int x, int y);
};
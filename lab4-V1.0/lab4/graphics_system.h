#pragma once

#include "SDL.h"
#include "SDL_image.h"

// The same Sprite iplementation as in the labs
class Sprite {
	SDL_Texture * texture;
	int width;
	int height;

public:

	Sprite(SDL_Texture * texture, int width, int height);

	// Destroys the sprite instance
	void destroy();

	// Draw the sprite at the given position using the graphics engine
	void draw(int x, int y, int angle);

	SDL_Texture* getTexture();
	int getWidth();
	int getHeight();
};


// This sub-system is in-charge of all sprite-drawing
// Follows the singleton design patter
class GraphicsSystem {

private:
	GraphicsSystem();		// private constructor to avoid multiple istances
	SDL_Renderer* renderer; // has a reference to the renderer, will make many render calls


public:
	static GraphicsSystem* getInstance();

	// Draw a sprite on a given position on the screen
	void draw(int x, int y, int angle, Sprite* sprite);

	// Create a Sprite object
	Sprite* createSprite(const char * path, int width, int height);

	// Set the render reference
	void setRenderer(SDL_Renderer* renderer);

	// Garbage collection is important in c++
	GraphicsSystem(GraphicsSystem const&) = delete;
	void operator=(GraphicsSystem const&) = delete;

};
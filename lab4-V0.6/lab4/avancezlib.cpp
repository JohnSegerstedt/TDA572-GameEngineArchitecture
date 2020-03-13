#pragma once
#include "avancezlib.h"
#include "SDL.h"
#include "sprite.h"
#include "variables.h"
#include "time_handler.h"
#include "SDL_image.h"
#include <sstream>
#include <iostream>


// Creates the main window. Returns true on success.
bool AvancezLib::init(int width, int height) {

	SDL_Log("Initializing the system...\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL failed the initialization: %s\n", SDL_GetError());
		return false;
	}

	//Create window
	window = SDL_CreateWindow("aVANCEZ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	//Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}

	TTF_Init();
	font = TTF_OpenFont("data/space_invaders.ttf", 12); //this opens a font style and sets a size
	if (font == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}


	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // todo, look at this later for background color

	// Initialize backgrounds
	backgrounds[0] = createSprite("data/background.png", SCREEN_WIDTH, SCREEN_HEIGHT);
	backgrounds[1] = createSprite("data/background-night.png", SCREEN_WIDTH, SCREEN_HEIGHT);

	//Clear screen
	SDL_RenderClear(renderer);


	SDL_Log("System up and running...\n");
	return true;
}


// Destroys the avancez library instance
void AvancezLib::destroy()
{
	SDL_Log("Shutting down the system\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_CloseFont(font);

	TTF_Quit();
	SDL_Quit();

}


bool AvancezLib::update() {
	bool go_on = true;
	SDL_Event event;


	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) go_on = false;

		if (event.type == SDL_KEYDOWN || SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case UP:
				key.up = event.type == SDL_KEYDOWN ;
				break;
			case DOWN:
				key.down = event.type == SDL_KEYDOWN;;
				break;
			case LEFT:
				key.left = event.type == SDL_KEYDOWN;
				break;
			case RIGHT:
				key.right = event.type == SDL_KEYDOWN;
				break;
			case FIRE:
				key.fire = event.type == SDL_KEYDOWN;
				break;
			case ESC:
				key.esc = event.type == SDL_KEYDOWN;
				break;
			case SPRINT:
				key.sprint = event.type == SDL_KEYDOWN;
				break;
			}
		}

	}

	//Update screen
	SDL_RenderPresent(renderer);

	//Clear screen
	SDL_RenderClear(renderer);

	//Draw background
	backgrounds[(*level + 1) % 2]->draw(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0);

	return go_on;
}


Sprite * AvancezLib::createSprite(const char * path, int width, int height) {

	SDL_Surface* surf = IMG_Load(path);

	if (surf == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Create texture from surface pixels
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surf);

	Sprite * sprite = new Sprite(renderer, texture, width, height);

	return sprite;
}

void AvancezLib::drawText(int x, int y, const char * msg) {
	SDL_Color black = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surf = TTF_RenderText_Solid(font, msg, black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(renderer, surf); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = { x, y, w, h };

	SDL_RenderCopy(renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(surf);
}

float AvancezLib::getElapsedTime() {
	return SDL_GetTicks() / 1000.f;
}

void AvancezLib::getKeyStatus(KeyStatus & keys) {
	keys.fire = key.fire;
	keys.up = key.up;
	keys.down = key.down;
	keys.left = key.left;
	keys.right = key.right;
	keys.sprint = key.sprint;
}


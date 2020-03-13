#pragma once
#include "avancezlib.h"
#include "SDL.h"
#include "variables.h"
#include "time_system.h"
#include "graphics_system.h"
#include "SDL_image.h"
#include <sstream>
#include <iostream>
#include <set>


// Creates the main window. Returns true on success.
bool AvancezLib::init(int width, int height) {

	go_on = true;

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

	//Create renderer for window and give to sub-engines
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	GraphicsSystem* graphics_engine;
	graphics_engine->getInstance()->setRenderer(renderer);
	text_engine.setRenderer(renderer);


	TTF_Init();
	TTF_Font* font = TTF_OpenFont("data/space_invaders.ttf", 12); //this opens a font style and sets a size
	if (font == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "font cannot be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}
	text_engine.setFont(font);


	//Initialize renderer color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // todo, look at this later for background color

	// Initialize backgrounds
	backgrounds[0] = graphics_engine->getInstance()->createSprite("data/background.png", SCREEN_WIDTH, SCREEN_HEIGHT);
	backgrounds[1] = graphics_engine->getInstance()->createSprite("data/background-night.png", SCREEN_WIDTH, SCREEN_HEIGHT);

	//Clear screen
	SDL_RenderClear(renderer);


	SDL_Log("System up and running...\n");
	return true;
}

void AvancezLib::terminate() {
	go_on = false;
}


// Destroys the avancez library instance
void AvancezLib::destroy(){
	SDL_Log("Shutting down the system\n");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	text_engine.destroyFont();

	TTF_Quit();
	SDL_Quit();

}


bool AvancezLib::update() {


	SDL_Event event;


	// ------------Update delegated sub-systems-------------------

	// Time Sub-system
	TimeSystem* time_engine;
	time_engine->getInstance()->update();

	// Input Sub-system
	input_engine.update();
	go_on = go_on ? input_engine.getGoOn() : false;


	// -------------------------------------------------


	//Update screen
	SDL_RenderPresent(renderer);

	//Clear screen
	SDL_RenderClear(renderer);

	//Draw background
	backgrounds[(*level + 1) % 2]->draw(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0);

	return go_on;
}

// Delegated command
void AvancezLib::drawText(int x, int y, const char * msg) {
	text_engine.drawText(x, y, msg);
}

// Delegated command
void AvancezLib::getKeyStatus(KeyStatus* keys) {
	input_engine.getKeyStatus(keys);
}


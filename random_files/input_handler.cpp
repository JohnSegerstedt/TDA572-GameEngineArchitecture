#pragma once

#include "input_handler.h"
#include "SDL.h"
#include <vector>
#include <map>
#include <iostream>


std::map<Binding, std::vector<int>> bindings; // todo make not vector
std::map<int, bool> keyboard; // Saves the state(true=pressed; false=released) of each SDL_Key.
int boundKeys[12];
int nBoundKeys = 0;

InputHandler* InputHandler::getInstance() {
	static InputHandler instance;	// Guaranteed to be destroyed. Instantiated on first use.
	return &instance;
}

InputHandler::InputHandler() {
	initialize();
}

void InputHandler::initialize() {
	bindings[UP] = { SDLK_w, SDLK_UP };
	bindings[LEFT] = { SDLK_a, SDLK_LEFT };
	bindings[DOWN] = { SDLK_s, SDLK_DOWN };
	bindings[RIGHT] = { SDLK_d, SDLK_RIGHT };
	bindings[SHOOT] = { SDLK_SPACE, -1 };
	bindings[MENU] = { SDLK_q, SDLK_ESCAPE };

	for (const auto& kv : bindings) {
		if (kv.second[0] != -1) boundKeys[nBoundKeys++] = kv.second[0];
		if (kv.second[1] != -1) boundKeys[nBoundKeys++] = kv.second[1];
	}
}

void InputHandler::update() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			std::cout << "KEY-DOWN \n";
			//if(keyboard[event.key.keysym.sym]) notify(ONKEYPRESSED, event.key)
			keyboard[event.key.keysym.sym] = true;
			break;
		case SDL_KEYUP:
			std::cout << "KEY-UP \n";
			keyboard[event.key.keysym.sym] = false;
			break;
		}
	}

	handleInput();
}

bool InputHandler::getPressed(Binding binding) {
	bindings;
	if (bindings[binding][0] != -1 && keyboard[bindings[binding][0]]) return true;
	if (bindings[binding][1] != -1 && keyboard[bindings[binding][1]]) return true;
	return false;
}

bool InputHandler::handleInput() {

	
	// todo make into a list to nicely be iterated through
	if (getPressed(UP))		notify(UP);
	if (getPressed(LEFT))	notify(LEFT);
	if (getPressed(DOWN))	notify(DOWN);
	if (getPressed(RIGHT))	notify(RIGHT);
	if (getPressed(SHOOT))	notify(SHOOT);
	if (getPressed(MENU)) {
		notify(MENU);
		return false;
	}
	return true;



	return true;
}


#include "input_system.h"
#include <iostream>

void InputSystem::getKeyStatus(KeyStatus* key) {
	(*key).fire		= keys.fire;
	(*key).up		= keys.up;
	(*key).down		= keys.down;
	(*key).left		= keys.left;
	(*key).right	= keys.right;
	(*key).pause	= keys.pause;
	(*key).sprint	= keys.sprint;
}

void InputSystem::update() {
	SDL_Event event;


	while (SDL_PollEvent(&event)) {
		
		if (event.type == SDL_QUIT) go_on = false;

		if (event.type == SDL_KEYDOWN || SDL_KEYUP) {

			// Put this outside the switch case since switches cannot do '||'...
					if (event.key.keysym.sym == UP_1 || event.key.keysym.sym == UP_2)		keys.up = event.type == SDL_KEYDOWN;
			else	if (event.key.keysym.sym == DOWN_1 || event.key.keysym.sym == DOWN_2)	keys.down = event.type == SDL_KEYDOWN;
			else	if (event.key.keysym.sym == LEFT_1 || event.key.keysym.sym == LEFT_2)	keys.left = event.type == SDL_KEYDOWN;
			else	if (event.key.keysym.sym == RIGHT_1 || event.key.keysym.sym == RIGHT_2) keys.right = event.type == SDL_KEYDOWN;
			
			//std::cout << "test" << "\n";

			switch (event.key.keysym.sym) {
			case FIRE:
				keys.fire = event.type == SDL_KEYDOWN;
				break;
			case PAUSE:
				keys.pause = event.type == SDL_KEYDOWN;
				break;
			case SPRINT:
				keys.sprint = event.type == SDL_KEYDOWN;
				break;
			}
		}

	}
}

bool InputSystem::getGoOn() {
	return go_on;
}
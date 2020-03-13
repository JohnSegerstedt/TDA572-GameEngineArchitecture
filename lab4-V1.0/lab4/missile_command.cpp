#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "variables.h"
#include "stdio.h"
#include "avancezlib.h"
#include "object_pool.h"

#include <set>

#include "component.h"
#include "game_object.h"

#include "rocket.h"
#include "bomb.h"
#include "player.h"

#include "game.h"

#include "time_system.h"

#include <thread>
#include <chrono>

// To have the system shut down successfully when given SDL_QUIT...
// ...and to successfully restart when game over.
void game(bool* restart) {
	*restart = false;

	AvancezLib system;
	TimeSystem *time_engine;

	system.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	Game game;
	game.Create(&system);
	game.Init();

	float lastTime = time_engine->getInstance()->getElapsedTime();
	while (system.update()) {
		float newTime = time_engine->getInstance()->getElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * time_engine->getInstance()->getGameSpeed();
		lastTime = newTime;

		*restart = game.UpdateGame(dt);

		game.Draw();
	}

	// clean up
	game.Destroy();
	system.destroy();
}

// Simple yet elegant main()
int main(int argc, char** argv) {

	bool play = true;
	while (play) game(&play);
	return 0;
}




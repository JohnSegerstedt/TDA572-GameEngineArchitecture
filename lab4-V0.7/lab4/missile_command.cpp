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

#include "time_handler.h"

#include <thread>
#include <chrono>

void game(bool* restart) {
	*restart = false;

	AvancezLib system;
	TimeHandler *timeHandler;

	system.init(SCREEN_WIDTH, SCREEN_HEIGHT);

	Game game;
	game.Create(&system);
	game.Init();

	float lastTime = system.getElapsedTime();
	while (system.update()) {
		float newTime = system.getElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * timeHandler->getInstance()->getGameSpeed();
		lastTime = newTime;

		*restart = game.UpdateGame(dt);

		game.Draw();
	}

	// clean up
	game.Destroy();
	system.destroy();
}

int main(int argc, char** argv) {

	bool play = true;
	while (play) game(&play);
	return 0;
}




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
#include "alien.h"
#include "aliens_grid.h"
#include "player.h"

#include "game.h"

#include "time_handler.h"
#include "input_handler.h"

int main(int argc, char** argv) {

	AvancezLib system;
	TimeHandler *timeHandler;

	system.init(640, 480);

	Game game;
	game.Create(&system);
	game.Init();

	float lastTime = system.getElapsedTime();
	while (system.update()) {
		float newTime = system.getElapsedTime();
		float dt = newTime - lastTime;
		dt = dt * timeHandler->getInstance()->getGameSpeed();
		lastTime = newTime;

		
		game.Update(dt);

		game.Draw();
	}

	// clean up
	game.Destroy();
	system.destroy();

	return 0;
}




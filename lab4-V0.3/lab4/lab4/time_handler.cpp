#pragma once

#include "time_handler.h"
#include "SDL.h"



TimeHandler::TimeHandler() {}

TimeHandler* TimeHandler::getInstance() {
	static TimeHandler instance;	// Guaranteed to be destroyed.
									// Instantiated on first use.
	return &instance;
}

// Should be called in the beginning of each frame
void TimeHandler::update() {
	last_frametime = getElapsed() - begin_frame_clock;
	begin_frame_clock = getElapsed();
}

float TimeHandler::getBeginFrameClock() {
	return begin_frame_clock;
}

float TimeHandler::getLastFrameTime() {
	return last_frametime;
}

float TimeHandler::getTimeLeft() {
	return TARGET_FRAMETIME - (getElapsed() - begin_frame_clock);
}

float TimeHandler::getFPS() {
	return (1000.0 / last_frametime);
}

// Return the total time spent in the game
int TimeHandler::getElapsed() {
	return SDL_GetTicks();
}

float TimeHandler::getGameSpeed() {
	return game_speed;
}

float TimeHandler::increaseGameSpeed() {
	return setGameSpeed(getGameSpeed() * 1.1f);
}

float TimeHandler::setGameSpeed(float newGameSpeed) {
	game_speed = newGameSpeed;
	return game_speed;
}



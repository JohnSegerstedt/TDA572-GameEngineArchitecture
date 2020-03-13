#pragma once

#include "time_system.h"



TimeSystem::TimeSystem() {}

TimeSystem* TimeSystem::getInstance() {
	static TimeSystem instance;	// Guaranteed to be destroyed.
									// Instantiated on first use.
	return &instance;
}

// Should be called in the beginning of each frame
void TimeSystem::update() {
	last_frametime = getElapsed() - begin_frame_clock;
	begin_frame_clock = getElapsed();
}

float TimeSystem::getElapsedTime() {
	return SDL_GetTicks() / 1000.f;
}

float TimeSystem::getBeginFrameClock() {
	return begin_frame_clock;
}

float TimeSystem::getLastFrameTime() {
	return last_frametime;
}

float TimeSystem::getTimeLeft() {
	return TARGET_FRAMETIME - (getElapsed() - begin_frame_clock);
}

float TimeSystem::getFPS() {
	return (1000.0 / last_frametime);
}

// Return the total time spent in the game
int TimeSystem::getElapsed() {
	return SDL_GetTicks();
}

float TimeSystem::getGameSpeed() {
	return game_speed;
}

float TimeSystem::increaseGameSpeed() {
	return setGameSpeed(getGameSpeed() * 1.01f);
}

float TimeSystem::setGameSpeed(float newGameSpeed) {
	game_speed = newGameSpeed;
	return game_speed;
}



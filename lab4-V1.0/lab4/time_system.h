#pragma once

#include "variables.h"
#include "SDL.h"

/*
timeHandler:
- Global time managing singleton
- Inspired by 'Time.deltaTime' in Unity
- Everything is in milliseconds
*/

class TimeSystem {

private:

	bool instantiated = false;

	TimeSystem();
	float begin_frame_clock = 0.0;
	float last_frametime = 0.0;
	float target_frametime = 1000.0 / TARGET_FPS;
	float game_speed = 1.0f;

public:

	static TimeSystem* getInstance();
	void update();				// Called exactly once per, and in beginning of, frame
	float getBeginFrameClock();	// Clock at begin of frame
	float getLastFrameTime();	// Time spent last frame (incl. sleep)
	float getElapsedTime();		// Get time since program start
	float getTimeLeft();		// Time left this frame
	float getFPS();
	int getElapsed();

	float getGameSpeed();
	float increaseGameSpeed();
	float setGameSpeed(float newGameSpeed);

	// Garbage collection is important in c++
	TimeSystem(TimeSystem const&) = delete;
	void operator=(TimeSystem const&) = delete;

};
#pragma once

#include "variables.h"


/*
timeHandler:
- Global time managing singleton
- Inspired by 'Time.deltaTime' in Unity
- Everything is in milliseconds
*/

class TimeHandler {

private:

	bool instantiated = false;

	TimeHandler();
	float begin_frame_clock = 0.0;
	float last_frametime = 0.0;
	float target_frametime = 1000.0 / TARGET_FPS;
	float game_speed = 1.0f;

public:

	static TimeHandler* getInstance();
	void update();				// Called exactly once per, and in beginning of, frame
	float getBeginFrameClock();	// Clock at begin of frame
	float getLastFrameTime();	// Time spent last frame (incl. sleep)
	float getTimeLeft();		// Time left this frame
	float getFPS();
	int getElapsed();

	float getGameSpeed();
	float increaseGameSpeed();
	float setGameSpeed(float newGameSpeed);

	TimeHandler(TimeHandler const&) = delete;
	void operator=(TimeHandler const&) = delete;

};
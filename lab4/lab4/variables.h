#pragma once

#include "SDL.h"

// input buttons
const SDL_KeyCode UP = SDLK_w;
const SDL_KeyCode DOWN = SDLK_s;
const SDL_KeyCode LEFT = SDLK_a;
const SDL_KeyCode RIGHT = SDLK_d;
const SDL_KeyCode FIRE = SDLK_SPACE;
const SDL_KeyCode ESC = SDLK_ESCAPE;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


// should be "#define":s ..?

const unsigned int	MAX_NUM_GAME_OBJECTS = 10000;
const unsigned int	NUM_LIVES = 2;

const unsigned int	MAX_NUM_ROCKETS = 32;
const unsigned int	MAX_NUM_BOMBS = 32;
const unsigned int	POINTS_PER_ALIEN = 100;
const float			FIRE_TIME_INTERVAL = .5f;
const float			BOMB_TIME_INTERVAL = 1.25f;
const float			PLAYER_SPEED = 300.0f;
const float			ROCKET_SPEED = 200.0f;
const float			ALIEN_SPEED = 40.0f;
const float			BOMB_SPEED = 120.0f;

const int			TARGET_FPS = 60;
const float			TARGET_FRAMETIME = (1000.0 / TARGET_FPS); // in milliseconds


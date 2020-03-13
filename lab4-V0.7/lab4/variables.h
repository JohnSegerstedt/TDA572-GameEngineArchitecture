#pragma once

#include "SDL.h"


enum Message { HIT, MISSILE_HIT, BOMB_HIT, BOMBER_HIT, CITY_HIT, LEVEL_WIN, NO_MSG };

// input buttons
const SDL_KeyCode UP_1 = SDLK_w;
const SDL_KeyCode UP_2 = SDLK_UP;
const SDL_KeyCode DOWN_1 = SDLK_s;
const SDL_KeyCode DOWN_2 = SDLK_DOWN;
const SDL_KeyCode LEFT_1 = SDLK_a;
const SDL_KeyCode LEFT_2 = SDLK_LEFT;
const SDL_KeyCode RIGHT_1 = SDLK_d;
const SDL_KeyCode RIGHT_2 = SDLK_RIGHT;
const SDL_KeyCode FIRE = SDLK_SPACE;
const SDL_KeyCode PAUSE = SDLK_ESCAPE;
const SDL_KeyCode SPRINT = SDLK_LSHIFT;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


#define	ROCKET_RADIUS	9
#define	MISSILE_RADIUS	8
#define BOMB_RADIUS 16
#define BOMBER_RADIUS 32
#define EXPLOSION_RADIUS 32


#define GRAVITY 200

#define NUM_BACKGROUNDS 2
#define NUM_LAYERS 4

// should be "#define":s ..?

const unsigned int EXPLOSION_SPRITES = 4;

const unsigned int	MAX_NUM_GAME_OBJECTS = 10000;
const unsigned int	STARTING_CITIES = 6;


const unsigned int	POINTS_PER_MISSILE = 3;
const unsigned int	POINTS_PER_BOMB = 5;
const unsigned int	POINTS_PER_BOMBER = 10;
const unsigned int	POINTS_PER_SAVED_CITY = 100;
const unsigned int	POINTS_PER_UNUSED_AMMO = 1;

const unsigned int	MAX_NUM_ROCKETS = 20;
const unsigned int	MAX_NUM_MISSILE = 100;
const unsigned int	MAX_NUM_BOMBS = 50;
const unsigned int	MAX_NUM_BOMBERS = 15;
const unsigned int	MAX_NUM_EXPLOSIONS = 50;

const float			FIRE_TIME_INTERVAL = .2f;
const float			PLAYER_SPEED = 300.0f;
const float			ROCKET_SPEED = 300.0f;
const float			MISSILE_SPEED = 70.0f;
const float			BOMB_SPEED = 120.0f;
const float			BOMBER_SPEED = 40.0f;

const float			STARTING_AMMO = 10;

const int			TARGET_FPS = 60;
const float			TARGET_FRAMETIME = (1000.0 / TARGET_FPS); // in milliseconds


#pragma once

#include <iostream>
#include <SDL_mixer.h>

enum Sound {THEME, ROCKET_SPAWNED, ROCKET_EXPLOSION, BOMB_SPAWNED, CITY_DESTROYED};

class AudioHandler {

private:

	Mix_Music* theme;
	Mix_Chunk* sound_rocket_fired;
	Mix_Chunk* sound_rocket_explosion;
	Mix_Chunk* sound_bomb_spawned;
	Mix_Chunk* sound_city_destroyed;

	AudioHandler();

public:

	static AudioHandler* getInstance();

	void PlaySound(Sound sound);
	void Quit();

	AudioHandler(AudioHandler const&) = delete;
	void operator=(AudioHandler const&) = delete;
};
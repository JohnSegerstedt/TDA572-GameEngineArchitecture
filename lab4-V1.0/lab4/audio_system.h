#pragma once

#include <iostream>
#include <SDL_mixer.h>

// The names of all music and sound effects
enum Sound {THEME, ROCKET_SPAWNED, ROCKET_EXPLOSION, BOMB_SPAWNED, CITY_DESTROYED};

// This sub-system is in charge of playing audio
// It follows the singleton pattern and is globally accessible
class AudioSystem {

private:

	// All different sounds
	Mix_Music* theme;
	Mix_Chunk* sound_rocket_fired;
	Mix_Chunk* sound_rocket_explosion;
	Mix_Chunk* sound_bomb_spawned;
	Mix_Chunk* sound_city_destroyed;

	AudioSystem();

public:

	static AudioSystem* getInstance();

	void PlaySound(Sound sound);
	void Quit();

	// Garbage collection is important in c++
	AudioSystem(AudioSystem const&) = delete;
	void operator=(AudioSystem const&) = delete;
};
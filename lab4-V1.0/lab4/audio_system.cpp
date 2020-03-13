#pragma once

#include "audio_system.h"

AudioSystem::AudioSystem() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) std::cout << "ERROR: " << Mix_GetError() << "\n";

	// Here is where all audio source file names are defined
	// This could be moved to "variables" to facilitate changing sound effects
	theme = Mix_LoadMUS("audio/theme.mp3");
	sound_rocket_fired = Mix_LoadWAV("audio/shot.wav");
	sound_rocket_explosion = Mix_LoadWAV("audio/explosion.wav");
	sound_bomb_spawned = Mix_LoadWAV("audio/bomb.wav");
	sound_city_destroyed = Mix_LoadWAV("audio/city_destroyed.wav");
}

AudioSystem* AudioSystem::getInstance() {
	static AudioSystem instance;	// Guaranteed to be destroyed.
									// Instantiated on first use.
	return &instance;
}

// Very simply method that attempts to play a given sound
void AudioSystem::PlaySound(Sound sound) {
	switch (sound) {
	case THEME:
		if (!Mix_PlayingMusic()) Mix_PlayMusic(theme, -1);
		break;
	case ROCKET_SPAWNED:
		Mix_PlayChannel(-1, sound_rocket_fired, 0);
		break;
	case ROCKET_EXPLOSION:
		Mix_PlayChannel(-1, sound_rocket_explosion, 0);
		break;
	case BOMB_SPAWNED:
		Mix_PlayChannel(-1, sound_bomb_spawned, 0);
		break;
	case CITY_DESTROYED:
		Mix_PlayChannel(-1, sound_city_destroyed, 0);
		break;
	}
}

// Garbage collection is important in c++
void AudioSystem::Quit() {
	Mix_FreeMusic(theme);
	Mix_FreeChunk(sound_rocket_explosion);
	Mix_FreeChunk(sound_bomb_spawned);
	Mix_FreeChunk(sound_city_destroyed);

	theme = nullptr;
	sound_rocket_explosion = nullptr;
	sound_bomb_spawned = nullptr;
	sound_city_destroyed = nullptr;

	Mix_Quit();
}
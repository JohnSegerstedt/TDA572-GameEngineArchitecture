#pragma once

#include "game.h"
#include "game_object.h"
#include "time_handler.h"
#include <sstream>




void Game::Create(AvancezLib* system) {
	SDL_Log("Game::Create");

	this->system = system;

	// Reserves memory for all object pools
	createMissilesSystem();
	createMissiles();
	createCities();
	createRockets();
	createPlayer();

	score = 0;
}

void Game::Init() {
	player->Init();
	missile_system->Init();

	enabled = true;
	game_over = false;
}

void Game::Update(float dt) {
	if (IsGameOver()) dt = 0.f;
	
	TimeHandler* timeHandler;
	timeHandler->getInstance()->update();

	for (auto go = game_objects.begin(); go != game_objects.end(); go++) (*go)->Update(dt);

	// check if there are still active aliens
	// if not, send a message to re-init the level
	bool any_city_still_alive = false;
	for (auto city = cities_pool.pool.begin(); city != cities_pool.pool.end(); city++) any_city_still_alive |= (*city)->alive;

	
	if (!any_city_still_alive && !game_over) { // level win!
		TimeHandler *timeHandler;
		timeHandler->getInstance()->increaseGameSpeed();
		missile_system->Init();
	}
	
}

void Game::Draw() { // todo, positions on screen is hardcoded here
	char msg[1024];
	sprintf_s(msg, "%07d", Score());
	system->drawText(SCREEN_WIDTH*0.45f, 32, msg);

	sprintf_s(msg, "level: %.f", 0);
	system->drawText(SCREEN_WIDTH*0.05f, 32, msg);

	TimeHandler *timeHandler;
	sprintf_s(msg, "bonus: %.1fX", timeHandler->getInstance()->getGameSpeed());
	system->drawText(SCREEN_WIDTH*0.85f, 32, msg);

	/*
	std::cout << timeHandler->getInstance()->getLastFrameTime() << "\n";
	int fps = (int)(1000.0 / timeHandler->getInstance()->getLastFrameTime());
	std::string fps_string = std::to_string(fps);
	char *fps_chars = &fps_string[0];
	system->drawText(100, 100, fps_chars);
	*/

	if (IsGameOver()) {
		sprintf_s(msg, "*** G A M E  O V E R ***");
		system->drawText(SCREEN_WIDTH * 0.4f, 8, msg);
	}
}

void Game::Receive(Message m) {

	// todo, fix issue where missiles hitting cities provides points
	if (m == MISSILE_HIT) {
		TimeHandler *timeHandler;
		score += POINTS_PER_MISSILE * timeHandler->getInstance()->getGameSpeed();
	}

	if (m == CITY_HIT) {
		if (--cities_alive == 0) game_over = true;
	}
}


bool Game::IsGameOver() {
	return game_over;
}

unsigned int Game::Score() {
	return score;
}

void Game::Destroy() {
	SDL_Log("Game::Destroy");

	for (auto go = game_objects.begin(); go != game_objects.end(); go++) (*go)->Destroy();

	life_sprite->destroy();

	rockets_pool.Destroy();
	missile_pool.Destroy();
	bombs_pool.Destroy();

	delete missile_system;
	delete player;
}

void Game::createPlayer() {
	player = new Player();
	PlayerBehaviourComponent * player_behaviour = new PlayerBehaviourComponent();
	player_behaviour->Create(system, player, &game_objects, &rockets_pool);
	RenderComponent * player_render = new RenderComponent();
	player_render->Create(system, player, &game_objects, "data/crosshair.png", 32, 32);
	player->Create();
	player->AddComponent(player_behaviour);
	player->AddComponent(player_render);
	player->AddReceiver(this);
	game_objects.insert(player);
}

void Game::createRockets() {
	rockets_pool.Create(30);
	for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++) {
		RocketBehaviourComponent * behaviour = new RocketBehaviourComponent();
		behaviour->Create(system, *rocket, &game_objects);
		RenderComponent * render = new RenderComponent();
		render->Create(system, *rocket, &game_objects, "data/rocket.png", 32, 32);
		(*rocket)->Create();
		(*rocket)->AddComponent(behaviour);
		(*rocket)->AddComponent(render);
	}
}

void Game::createMissilesSystem() {
	missile_system = new MissileSystem();
	MissileSystemBehaviourComponent  * missile_system_behaviour = new MissileSystemBehaviourComponent();
	missile_system_behaviour->Create(system, missile_system, &game_objects, &missile_pool, &cities_pool);
	missile_system->Create();
	missile_system->AddComponent(missile_system_behaviour);
	game_objects.insert(missile_system);
}

void Game::createMissiles() {
	missile_pool.Create(55);
	for (auto missile = missile_pool.pool.begin(); missile != missile_pool.pool.end(); missile++) {
		MissileBehaviourComponent * missile_behaviour = new MissileBehaviourComponent();
		missile_behaviour->Create(system, *missile, &game_objects);
		RenderComponent * missile_render = new RenderComponent();
		missile_render->Create(system, *missile, &game_objects, "data/missile.png", 32, 32);
		CollideComponent * missile_coll = new CollideComponent();
		missile_coll->Create(system, *missile, &game_objects, (ObjectPool<GameObject>*)&rockets_pool);
		(*missile)->Create();
		(*missile)->AddComponent(missile_behaviour);
		(*missile)->AddComponent(missile_render);
		(*missile)->AddComponent(missile_coll);
		(*missile)->AddReceiver(this);
	}

}

void Game::createCities() {
	cities_pool.Create(6);
	int i = 1;
	for (auto city = cities_pool.pool.begin(); city != cities_pool.pool.end(); city++) {
		CityRenderComponent * city_render = new CityRenderComponent();
		city_render->Create(system, *city, &game_objects, "data/city_alive.png", "data/city_dead.png", 32);
		CollideComponent * city_coll = new CollideComponent();
		city_coll->Create(system, *city, &game_objects, (ObjectPool<GameObject>*)&missile_pool);
		(*city)->Create();
		(*city)->AddComponent(city_render);
		(*city)->AddComponent(city_coll);
		(*city)->AddReceiver(this);
		(*city)->Init(i++ * (SCREEN_WIDTH / 8.0f), SCREEN_HEIGHT * 0.9f);
		if (i == 4) i++;
		game_objects.insert(*city);
	}
}
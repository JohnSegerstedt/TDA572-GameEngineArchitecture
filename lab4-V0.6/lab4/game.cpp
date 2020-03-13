#pragma once

#include "game.h"
#include "game_object.h"
#include "time_handler.h"
#include "audio_handler.h"
#include <sstream>




void Game::Create(AvancezLib* system) {

	SDL_Log("Game::Create");

	this->system = system;

	// Reserves memory for all object pools
	bad_stuff.insert((ObjectPool<GameObject>*) &missile_pool);
	bad_stuff.insert((ObjectPool<GameObject>*) &bomb_pool);
	bad_stuff.insert((ObjectPool<GameObject>*) &bomber_pool);
	createPlayer();
	createMissilesSystem();
	createMissiles();
	createBombs();
	createBombers();
	createExplosions();
	createRockets();
	createCities();
	score = 0;


}

void Game::Init() {
	system->level = &level;
	player->Init();
	missile_system->Init();


	AudioHandler* audioHandler;
	audioHandler->getInstance()->PlaySound(THEME);

	enabled = true;
	game_over = false;
}

void Game::Update(float dt) {
	if (IsGameOver()) dt = 0.f;
	
	TimeHandler* timeHandler;
	timeHandler->getInstance()->update();

	for (auto go = game_objects.begin(); go != game_objects.end(); go++) (*go)->Update(dt);
	
}

void Game::Draw() { // todo, positions on screen is hardcoded here
	char msg[1024];
	sprintf_s(msg, "%07d", Score());
	system->drawText(SCREEN_WIDTH*0.45f, 32, msg);

	sprintf_s(msg, "level: %d", level);
	system->drawText(SCREEN_WIDTH*0.05f, 32, msg);

	sprintf_s(msg, "ammo: %d", ammo);
	system->drawText(SCREEN_WIDTH*0.85f, 32, msg);

	if (IsGameOver()) {
		sprintf_s(msg, "*** G A M E  O V E R ***");
		system->drawText(SCREEN_WIDTH * 0.4f, 8, msg);
	}
}

void Game::Receive(Message m) {

	// todo, fix issue where missiles hitting cities provides points
	if (m == MISSILE_HIT) {
		score += POINTS_PER_MISSILE * level;
		ammo++;
	}

	else if (m == BOMB_HIT) {
		score += POINTS_PER_BOMB * level;
		ammo++;
	}

	else if (m == BOMBER_HIT) {
		score += POINTS_PER_BOMBER * level;
		ammo++;
	}

	else if (m == CITY_HIT) {
		if (--cities_alive == 0) game_over = true;
	}

	else if (m == LEVEL_WIN) {

		score += POINTS_PER_SAVED_CITY * cities_alive  * level;
		score += POINTS_PER_SAVED_CITY * ammo  * level;

		//ammo = STARTING_AMMO;
		level++;
		missile_system->Init();
	}

	else if (m == GAME_OVER) {
		// todo
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
	explosion_pool.Destroy();
	bomb_pool.Destroy();

	delete missile_system;
	delete player;
}

void Game::createPlayer() {
	player = new Player();
	PlayerBehaviourComponent * player_behaviour = new PlayerBehaviourComponent();
	player_behaviour->Create(system, player, &game_objects, &rockets_pool, &ammo);
	RenderComponent * player_render = new RenderComponent();
	player_render->Create(system, player, &game_objects, "data/crosshair.png");
	player->Create(3);
	player->AddComponent(player_behaviour);
	player->AddComponent(player_render);
	player->AddReceiver(this);
	game_objects.insert(player);
	//bla.insert(*reinterpret_cast<GameObject*>(player));
	//bla_ptr.insert(reinterpret_cast<GameObject*>(player));
}

void Game::createRockets() {
	rockets_pool.Create(MAX_NUM_ROCKETS);
	for (auto rocket = rockets_pool.pool.begin(); rocket != rockets_pool.pool.end(); rocket++) {
		(*rocket)->radius = ROCKET_RADIUS;
		RocketBehaviourComponent * behaviour = new RocketBehaviourComponent();
		behaviour->Create(system, *rocket, &game_objects, &explosion_pool);
		RenderComponent * render = new RenderComponent();
		render->Create(system, *rocket, &game_objects, "data/rocket.png");

		CollideComponent * rocket_coll = new CollideComponent();
		rocket_coll->Create(system, *rocket, &game_objects, &bad_stuff);
		(*rocket)->Create(2);
		(*rocket)->AddComponent(behaviour);
		(*rocket)->AddComponent(render);
		(*rocket)->AddComponent(rocket_coll);
		//game_objects.insert(*rocket);
		//game_objects_new.insert(GameObject());
		//bla.insert(**rocket);
		//bla_ptr.insert(*rocket);

	}
}

void Game::createMissilesSystem() {
	missile_system = new MissileSystem();
	MissileSystemBehaviourComponent  * missile_system_behaviour = new MissileSystemBehaviourComponent();
	missile_system_behaviour->Create(system, missile_system, &game_objects, &missile_pool, &bomber_pool, &cities_pool, &level);
	missile_system->Create(2);
	missile_system->AddComponent(missile_system_behaviour);
	missile_system->AddReceiver(this);
	game_objects.insert(missile_system);
}

void Game::createBombs() {
	bomb_pool.Create(MAX_NUM_BOMBS);
	for (auto bomb = bomb_pool.pool.begin(); bomb != bomb_pool.pool.end(); bomb++) {
		(*bomb)->radius = BOMB_RADIUS;
		BombBehaviourComponent * bomb_behaviour = new BombBehaviourComponent();
		bomb_behaviour->Create(system, *bomb, &game_objects);
		RenderComponent * bomb_render = new RenderComponent();
		bomb_render->Create(system, *bomb, &game_objects, "data/bomb.png");
		(*bomb)->Create(2);
		(*bomb)->AddComponent(bomb_behaviour);
		(*bomb)->AddComponent(bomb_render);
		(*bomb)->AddReceiver(this);
	}
}

void Game::createBombers() {
	bomber_pool.Create(MAX_NUM_BOMBERS);
	for (auto bomber = bomber_pool.pool.begin(); bomber != bomber_pool.pool.end(); bomber++) {
		(*bomber)->radius = BOMBER_RADIUS;
		BomberBehaviourComponent * bomber_behaviour = new BomberBehaviourComponent();
		bomber_behaviour->Create(system, *bomber, &game_objects, &bomb_pool);
		RenderComponent * bomber_render = new RenderComponent();
		bomber_render->Create(system, *bomber, &game_objects, "data/bomber.png");
		(*bomber)->Create(2);
		(*bomber)->AddComponent(bomber_behaviour);
		(*bomber)->AddComponent(bomber_render);
		(*bomber)->AddReceiver(this);
	}
}
void Game::createMissiles() {
	missile_pool.Create(MAX_NUM_MISSILE);
	for (auto missile = missile_pool.pool.begin(); missile != missile_pool.pool.end(); missile++) {
		(*missile)->radius = MISSILE_RADIUS;
		MissileBehaviourComponent * missile_behaviour = new MissileBehaviourComponent();
		missile_behaviour->Create(system, *missile, &game_objects);
		RenderComponent * missile_render = new RenderComponent();
		missile_render->Create(system, *missile, &game_objects, "data/missile.png");
		(*missile)->Create(2);
		(*missile)->AddComponent(missile_behaviour);
		(*missile)->AddComponent(missile_render);
		(*missile)->AddReceiver(this);
		//game_objects.insert(*missile);
	}

}

void Game::createCities() {
	cities_pool.Create(6);
	int i = 1;
	for (auto city = cities_pool.pool.begin(); city != cities_pool.pool.end(); city++) {
		CityRenderComponent * city_render = new CityRenderComponent();
		city_render->Create(system, *city, &game_objects, "data/city_alive-0.png", "data/city_dead-0.png", 32);
		CollideComponent * city_coll = new CollideComponent();
		city_coll->Create(system, *city, &game_objects, &bad_stuff);
		(*city)->Create(1);
		(*city)->AddComponent(city_render);
		(*city)->AddComponent(city_coll);
		(*city)->AddReceiver(this);
		(*city)->Init(i++ * (SCREEN_WIDTH / 8.0f), SCREEN_HEIGHT * 0.9f);
		if (i == 4) i++;
		game_objects.insert(*city);
		//bla_ptr.insert(*city);
		//bla.insert(**city);
	}
}

void Game::createExplosions() {
	explosion_pool.Create(MAX_NUM_EXPLOSIONS);
	for (auto explosion = explosion_pool.pool.begin(); explosion != explosion_pool.pool.end(); explosion++) {
		(*explosion)->radius = EXPLOSION_RADIUS;
		//ExplosionBehaviourComponent * behaviour = new ExplosionBehaviourComponent();
		//behaviour->Create(system, *explosion, &game_objects);
		ExplosionRenderComponent * render = new ExplosionRenderComponent();
		std::set<const char *> new_sprites;
		new_sprites.insert("data/explosion-0.png");
		new_sprites.insert("data/explosion-1.png");
		new_sprites.insert("data/explosion-2.png");
		new_sprites.insert("data/explosion-3.png");
		render->Create(system, *explosion, &game_objects, new_sprites, 64);
		//(*explosion)->AddReceiver(render);
		(*explosion)->Create(2);
		//(*explosion)->AddComponent(behaviour);
		(*explosion)->AddComponent(render);
		//game_objects.insert(*rocket);
		//game_objects_new.insert(GameObject());
		//bla.insert(**rocket);
		//bla_ptr.insert(*rocket);
		CollideComponent * explosion_coll = new CollideComponent();
		explosion_coll->Create(system, *explosion, &game_objects, &bad_stuff);
		(*explosion)->AddComponent(explosion_coll);

	}
}
#pragma once

#include "game_object.h"
#include "rocket.h"
#include "bomb.h"
#include "player.h"
#include "city.h"
#include "missile.h"
#include "missile_system.h"

class Game : public GameObject {

	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/
	std::set<CollideComponent*> colliders;

	AvancezLib* system;

	ObjectPool<Rocket> rockets_pool;	// used to instantiate rockets
	ObjectPool<Missile> missile_pool;
	ObjectPool<Bomb> bombs_pool;
	ObjectPool<City> cities_pool;


	

	Player * player;
	MissileSystem * missile_system;

	Sprite * life_sprite;
	bool game_over;

	unsigned int score = 0;

	unsigned int cities_alive = STARTING_CITIES;

public:

	virtual void Create(AvancezLib* system);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Receive(Message m);
	bool IsGameOver();
	unsigned int Score();
	virtual void Destroy();


private:
	void createPlayer();
	void createRockets();
	void createMissiles();
	void createMissilesSystem();
	void createCities();
};
#pragma once

#include "bomber.h"
#include "game_object.h"
#include "rocket.h"
#include "bomb.h"
#include "player.h"
#include "city.h"
#include "missile.h"
#include "missile_system.h"
#include "explosion.h"
#include  <queue>

struct comp {
	bool operator() (int a, int b) const {
		return true;
	}
};

class Game : public GameObject {

	//std::set<GameObject, GameObject::game_object_compare> game_objects_new;
	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/
	std::set<ObjectPool<GameObject>*> bad_stuff;


	AvancezLib* system;

	ObjectPool<Rocket> rockets_pool;	// used to instantiate rockets
	ObjectPool<Missile> missile_pool;
	ObjectPool<Bomb> bomb_pool;
	ObjectPool<Bomber> bomber_pool;
	ObjectPool<City> cities_pool;
	ObjectPool<Explosion> explosion_pool;



	

	Player * player;
	MissileSystem * missile_system;

	Sprite * life_sprite;
	bool game_over;

	unsigned int level = 1;
	unsigned int score = 0;
	unsigned int ammo = STARTING_AMMO;
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
	void createBombs();
	void createBombers();
	void createMissiles();
	void createMissilesSystem();
	void createCities();
	void createExplosions();
};
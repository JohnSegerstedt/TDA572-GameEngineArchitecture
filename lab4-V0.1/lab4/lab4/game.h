#pragma once

#include "game_object.h"
#include "rocket.h"
#include "alien.h"
#include "bomb.h"
#include "player.h"
#include "aliens_grid.h"


class Game : public GameObject {

	std::set<GameObject*> game_objects;	// http://www.cplusplus.com/reference/set/set/

	AvancezLib* system;

	ObjectPool<Rocket> rockets_pool;	// used to instantiate rockets
	ObjectPool<Alien> aliens_pool;
	ObjectPool<Bomb> bombs_pool;

	Player * player;
	AliensGrid * aliens_grid;

	Sprite * life_sprite;
	bool game_over;

	unsigned int score = 0;

public:

	virtual void Create(AvancezLib* system);
	virtual void Init();
	virtual void Update(float dt);
	virtual void Draw();
	virtual void Receive(Message m);
	bool IsGameOver();
	unsigned int Score();
	virtual void Destroy();
};
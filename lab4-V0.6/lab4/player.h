#pragma once

#include "time_handler.h"
#include "component.h"
#include "object_pool.h"
#include "rocket.h"

class PlayerBehaviourComponent : public Component {
	float time_fire_pressed;	// time from the last time the fire button was pressed
	ObjectPool<Rocket> * rockets_pool;
	unsigned int* ammo;

public:
	virtual ~PlayerBehaviourComponent() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Rocket> * rockets_pool, unsigned int* ammo_ptr);

	virtual void Init();

	virtual void Update(float dt);


	// move the player relative to its current position
	// param move depends on the time, so the player moves always at the same speed on any computer
	void MoveRelative(float x, float y);

	// return true if enough time has passed from the previous rocket
	bool CanFire();

	void Fire();
};


// the main player
class Player : public GameObject {

public:

	virtual void Init();
	virtual void Receive(Message m);

};

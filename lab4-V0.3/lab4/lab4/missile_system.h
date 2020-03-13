#pragma once



#include "time_handler.h"
#include "missile.h"

class MissileSystemBehaviourComponent : public Component {
	float timeSinceLastMissileLaunch = 0;
	float cooldown = 1; // in seconds
	bool change_direction;

	ObjectPool<Missile> * missile_pool;
	ObjectPool<City> * cities_pool;

public:
	virtual ~MissileSystemBehaviourComponent() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Missile> * missile_pool, ObjectPool<City> * cities_pool) {
		Component::Create(system, go, game_objects);
		this->missile_pool = missile_pool;
		this->cities_pool = cities_pool;
	}

	virtual void Init() {

	}

	void LaunchMissile() {
		Missile * missile = missile_pool->FirstAvailable();
		if (missile != NULL) {
			City * city = cities_pool->SelectRandom();
			if (city != NULL) {
				missile->Init(SCREEN_WIDTH * (rand() * 0.9f / (float)RAND_MAX) + SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.1f, SCREEN_WIDTH * (rand() * 0.9f / (float)RAND_MAX) + SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT * 0.95f);
				game_objects->insert(missile);
			}
		}
	}

	virtual void Update(float dt) {

		// todo make more interesting
		timeSinceLastMissileLaunch += dt;
		if (timeSinceLastMissileLaunch > cooldown) {
			//std::cout << timeSinceLastMissileLaunch << "\n";
			timeSinceLastMissileLaunch -= cooldown;
			LaunchMissile();
		}

	}


};



class MissileSystem : public GameObject {
public:

	virtual ~MissileSystem() { SDL_Log("MissileSystem::~MissileSystem"); }



	virtual void Init() {
		SDL_Log("MissileSystem::Init");
		GameObject::Init();
	}


};


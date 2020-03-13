#pragma once



#include "time_system.h"
#include "missile.h"
#include <algorithm>

// This class is in charge over spawning Missiles and Bombers
class MissileSystemBehaviourComponent : public Component {
	float current_level_time;
	float max_level_time;

	float timeSinceLastBomberLaunch;
	float bomber_num;
	float bomber_wait[1000];
	int bomber_index;

	float timeSinceLastMissileLaunch;
	float missiles_num;
	float missile_wait[1000];
	int missile_index;

	unsigned int* level;

	ObjectPool<Missile> * missile_pool;
	ObjectPool<Bomber> * bomber_pool;
	ObjectPool<City> * cities_pool;

public:
	virtual ~MissileSystemBehaviourComponent() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Missile> * missile_pool, ObjectPool<Bomber> * bomber_pool, ObjectPool<City> * cities_pool, unsigned int* level) {
		Component::Create(system, go, game_objects); 
		this->missile_pool = missile_pool;
		this->bomber_pool = bomber_pool;
		this->cities_pool = cities_pool;
		this->level = level;
	}

	virtual void Init() {
		int missileWait = 0;
		missiles_num = std::min(30.0, (rand() * (*level) * 5.0 / (float)RAND_MAX) + 10);
		for (int i = 0; i < missiles_num; i++) {
			missile_wait[i] = std::max(0, int(rand() * std::max(2, int(5 - *level)) / (float)RAND_MAX));
			missileWait += missile_wait[i];
		}

		int bomberWait = 0;
		bomber_num = std::min(10.0, (rand() * (*level) * 1.0 / (float)RAND_MAX) + 1);
		for (int i = 0; i < bomber_num; i++){
			bomber_wait[i] = std::max(3, int(rand() * std::max(1, int(15 - (*level))) / (float)RAND_MAX));
			bomberWait += bomber_wait[i];
		}

		
		max_level_time = std::max(missileWait, bomberWait) + 10;
		timeSinceLastBomberLaunch = 0;
		timeSinceLastMissileLaunch = 0;
		current_level_time = 0;
		missile_index = 0;
		bomber_index = 0;
	}

	virtual void Update(float dt) {
		
		if (missile_index < missiles_num) {
			timeSinceLastMissileLaunch += dt;
			if (timeSinceLastMissileLaunch > missile_wait[missile_index]) {
				timeSinceLastMissileLaunch -= missile_wait[missile_index];
				missile_index++;
				LaunchMissile();
			}
		}

		if (bomber_index < bomber_num) {
			timeSinceLastBomberLaunch += dt;
			if (timeSinceLastBomberLaunch > bomber_wait[bomber_index]) {
				timeSinceLastBomberLaunch -= bomber_wait[bomber_index];
				bomber_index++;
				LaunchBomber();
			}
		}

		current_level_time += dt;
		if (current_level_time > max_level_time) {
			go->Send(LEVEL_WIN);
		}

	}


	void LaunchBomber() {
		Bomber * bomber = bomber_pool->FirstAvailable();
		if (bomber != nullptr) {
			bomber->Init();
			game_objects->insert(bomber);
		}

	}

	void LaunchMissile() {
		Missile * missile = missile_pool->FirstAvailable();
		if (missile != NULL) {
			City * city = cities_pool->SelectRandom(); // todo aim at cities?	
			if (city != NULL) {
				int posX = SCREEN_WIDTH * (rand() * 0.7f / (float)RAND_MAX) + SCREEN_WIDTH * 0.15f;
				int posY = SCREEN_HEIGHT * 0.1f;
				int targetX = SCREEN_WIDTH * (rand() * 0.7f / (float)RAND_MAX) + SCREEN_WIDTH * 0.15f;
				int targetY = SCREEN_HEIGHT * 0.95f;
				if (city->alive) {
					posX = fmax(SCREEN_WIDTH * 0.1f, fmin(SCREEN_WIDTH * 0.9f, (city->horizontalPosition + SCREEN_WIDTH * (rand() * 0.4f / (float)RAND_MAX) - SCREEN_WIDTH * 0.2f)));
					targetX = city->horizontalPosition;
					targetY = city->verticalPosition;
				}
				missile->Init(posX, posY, targetX, targetY);
				game_objects->insert(missile);
			}
		}
	}
	



};



class MissileSystem : public GameObject {
public:

	virtual ~MissileSystem() { SDL_Log("MissileSystem::~MissileSystem"); }



	virtual void Init() {
		GameObject::Init();
	}


};


#pragma once

#include "bomb.h"
#include "object_pool.h"
#include "audio_system.h"
#include <algorithm>
#include <iostream>

// The green bombers
class Bomber : public GameObject {
public:

	bool goRight = 1;

	virtual ~Bomber() {
	}



	virtual void Init() {

		bool goRight = (0.5 > rand() / (float)RAND_MAX);
		float x = goRight ? 0 : SCREEN_WIDTH;
		float y = SCREEN_HEIGHT * (rand() * 0.3f / (float)RAND_MAX) + SCREEN_HEIGHT * 0.2f;

		this->horizontalPosition = x;
		this->verticalPosition = y;

		bool goUp = (rand() / (float)RAND_MAX) > 0.5f;
		float targetX = goRight ? SCREEN_WIDTH : 0;
		float targetY = y + SCREEN_HEIGHT * (rand() * 0.4f / (float)RAND_MAX) * (goUp ? -1.0 : 1.0);
		targetY = std::max(std::min(SCREEN_HEIGHT * 0.7f, targetY), SCREEN_HEIGHT * 0.15f);

		Vector2D direction = (Vector2D(targetX, targetY).operator-(Vector2D(x, y))).normalize();
		this->velocity = direction * BOMBER_SPEED;
		this->orientation = atan2(direction.y, direction.x) * 180.0f / M_PI;

		GameObject::Init();
		this->goRight = goRight;
	}

	virtual void Receive(Message m) {
		if (!enabled) return;

		if (m == HIT) {
			enabled = false;
			Send(BOMBER_HIT);
		}
	}


};

class BomberBehaviourComponent : public Component {
	float timeSinceLastBomb = 0;
	float bomb_cooldown = 3;

	ObjectPool<Bomb> * bomb_pool;


public:
	virtual ~BomberBehaviourComponent() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Bomb> * bomb_pool) {
		Component::Create(system, go, game_objects);
		this->bomb_pool = bomb_pool;
	}

	virtual void Init() {

	}

	virtual void Update(float dt) {

		timeSinceLastBomb += dt;
		if (timeSinceLastBomb > bomb_cooldown) {
			timeSinceLastBomb -= bomb_cooldown;
			LaunchBomb();
		}

		go->horizontalPosition += go->velocity.x * dt;
		go->verticalPosition += go->velocity.y * dt;

	}


	void LaunchBomb() {
		Bomb * bomb = bomb_pool->FirstAvailable();
		if (bomb != NULL) {
			AudioSystem* audio_system;
			audio_system->getInstance()->PlaySound(BOMB_SPAWNED);
			int posX = go->horizontalPosition;
			int posY = go->verticalPosition;
			int targetX = SCREEN_WIDTH * (rand() * 0.7f / (float)RAND_MAX) + SCREEN_WIDTH * 0.15f;
			int targetY = SCREEN_HEIGHT * 0.95f;
			bomb->Init(posX, posY, targetX, targetY);
			game_objects->insert(bomb);
		} else {
			std::cout << "BOMBER FAILED!";
		}
	}

};
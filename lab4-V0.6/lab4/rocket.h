#pragma once

#include "variables.h"
#include "vector2D.h"
#include "explosion.h"
#include "audio_handler.h"
#include <iostream>

// rockets are shot by the player towards the aliens
class Rocket : public GameObject {

public:

	Vector2D target;

	virtual void Init(float x, float y) {
		SDL_Log("Rocket::Init");
		GameObject::Init();


		horizontalPosition = SCREEN_WIDTH / 2.0;
		verticalPosition = SCREEN_HEIGHT * 0.9f;

		target = Vector2D(x, y);
		Vector2D direction = target.operator-(Vector2D(horizontalPosition, verticalPosition)).normalize();
		velocity = direction * ROCKET_SPEED;
		this->orientation = atan2(direction.y, direction.x) * 180.0f / M_PI;

		horizontalPosition += direction.x * 10.0f;
		verticalPosition += direction.y * 10.0f;

	}

	virtual void Receive(Message m) {
		if (!enabled) return;

		if (m == HIT) {
			for (auto it = components.begin(); it != components.end(); it++) (*it)->Receive(HIT);
			enabled = false;
		}
	}

};

class RocketBehaviourComponent : public Component {

	ObjectPool<Explosion> * explosion_pool;


public:

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Explosion> * explosion_pool) {
		Component::Create(system, go, game_objects);
		this->explosion_pool = explosion_pool;
	}

	void Explode() {
		Explosion * explosion = explosion_pool->FirstAvailable();
		if (explosion != NULL) {
			explosion->Init(go->horizontalPosition, go->verticalPosition, go->orientation);
			game_objects->insert(explosion);
			AudioHandler* audioHandler;
			audioHandler->getInstance()->PlaySound(ROCKET_EXPLOSION);
		}
	}

	void Update(float dt) {

		// todo make more advanced?
		go->horizontalPosition += go->velocity.x * dt;
		go->verticalPosition += go->velocity.y * dt;

		// Removed if leaves screen
		if (go->horizontalPosition + go->radius < 0) go->enabled = false;
		else if (go->horizontalPosition - go->radius > SCREEN_WIDTH) go->enabled = false;
		else if (go->verticalPosition + go->radius < 0) go->enabled = false;
		else if (go->verticalPosition + go->radius > SCREEN_HEIGHT) go->enabled = false;

		// Removed if reached target
		// todo make explosion
		Rocket *rocket = reinterpret_cast<Rocket*>(go);
		if (rocket != nullptr) if (rocket->target.operator-(Vector2D(go->horizontalPosition, go->verticalPosition)).length() < go->radius) {
			go->enabled = false;
			Explode();
		}
	}

	virtual void Receive(Message m) {
		if (!go->enabled) return;

		if (m == HIT) {
			Explode();
		}
	}
};



#pragma once

#include "variables.h"
#include "vector2D.h"
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
			enabled = false;
			SDL_Log("Rocket::Hit");
		}
	}

};

class RocketBehaviourComponent : public Component {
public:

	void Update(float dt) {

		// todo make more advanced?
		go->horizontalPosition += go->velocity.x * dt;
		go->verticalPosition += go->velocity.y * dt;

		// Removed if leaves screen
		if (go->horizontalPosition + go->width / 2.0 < 0) go->enabled = false;
		else if (go->horizontalPosition - go->width / 2.0 > SCREEN_WIDTH) go->enabled = false;
		else if (go->verticalPosition + go->width / 2.0 < 0) go->enabled = false;
		else if (go->verticalPosition + go->width > SCREEN_HEIGHT) go->enabled = false;

		// Removed if reached target
		// todo make explosion
		Rocket *rocket = reinterpret_cast<Rocket*>(go);
		if(rocket != nullptr) if (rocket->target.operator-(Vector2D(go->horizontalPosition, go->verticalPosition)).length() < go->width / 2.0f) go->enabled = false;
	}
};



#pragma once
#include "game_object.h"
#include "SDL.h"
#include "variables.h"


class Bomb : public GameObject {



public:

	Vector2D target;

	virtual void Init(double xPos, double yPos, double targetX, double targetY) {
		this->horizontalPosition = xPos;
		this->verticalPosition = yPos;
		Vector2D direction = (Vector2D(targetX, targetY).operator-(Vector2D(xPos, yPos))).normalize();
		//Vector2D direction = (Vector2D(targetX, SCREEN_HEIGHT * 0.5f).operator-(Vector2D(xPos, yPos))).normalize();
		this->velocity = direction * MISSILE_SPEED;
		this->orientation = atan2(direction.y, direction.x) * 180.0f / M_PI;
		//std::cout << atan2(direction.y, direction.x) << "\n";
		target = Vector2D(targetX, targetY);
		enabled = true;
	}

	virtual void Receive(Message m) {
		if (!enabled)
			return;

		if (m == HIT) {
			Send(BOMB_HIT);
			enabled = false;
		}
	}

};



class BombBehaviourComponent : public Component {
public:
	virtual ~BombBehaviourComponent() {}

	virtual void Update(float dt) {

		//Bomb* bomb = (Bomb *)go;

		/*
		// make velocity face down more
		Vector2D direction = Vector2D(go->velocity.x, go->velocity.y);
		direction.gravity(dt, &direction);
		go->velocity.x = direction.x;
		go->velocity.y = direction.y;
		double angle = direction.getAngle(direction);
		go->orientation = angle;
		std::cout << go->orientation << " | " << go->velocity.x << " | " << go->velocity.y << "\n";
		*/

		float angleDiff = (fmod(go->orientation, 360) < 90) ? -1.0f * GRAVITY * dt : GRAVITY * dt;
		go->velocity.x += tan(angleDiff) * M_PI / 180.0f;
		go->velocity.y += cos(angleDiff) * M_PI / 180.0f;
		go->orientation = atan2(go->velocity.y, go->velocity.x) * 180.0f / M_PI;


		go->horizontalPosition += go->velocity.x * dt;
		go->verticalPosition += go->velocity.y * dt;

		// todo add missile explosion
		//if (go->verticalPosition > SCREEN_HEIGHT - go->radius) go->enabled = false;
	}

};
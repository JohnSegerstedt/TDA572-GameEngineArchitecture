#pragma once
#include "game_object.h"
#include "SDL.h"
#include "variables.h"


class Missile : public GameObject {

	

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
			enabled = false;
			Send(MISSILE_HIT);
		}
	}

};



class MissileBehaviourComponent : public Component {
public:
	virtual ~MissileBehaviourComponent() {}

	virtual void Update(float dt) {

		//Missile* missile = (Missile *)go;
		
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


		go->horizontalPosition += go->velocity.x * dt;
		go->verticalPosition += go->velocity.y * dt;

		// todo add missile explosion
		//if (go->verticalPosition > SCREEN_HEIGHT - go->radius) go->enabled = false;
	}

};
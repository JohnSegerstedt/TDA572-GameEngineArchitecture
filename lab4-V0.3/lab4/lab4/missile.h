#pragma once
#include "game_object.h"
#include "SDL.h"
#include "variables.h"


class Missile : public GameObject {

public:

	virtual void Init(double xPos, double yPos, double targetX, double targetY) {
		this->horizontalPosition = xPos;
		this->verticalPosition = yPos;
		Vector2D direction = (Vector2D(targetX, targetY).operator-(Vector2D(xPos, yPos))).normalize();
		this->velocity = direction * MISSILE_SPEED;
		this->orientation = atan2(direction.y, direction.x) * 180.0f / M_PI;
		//std::cout << atan2(direction.y, direction.x) << "\n";
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
		Missile * missile = (Missile *)go;

		go->horizontalPosition += go->velocity.x * dt;
		go->verticalPosition += go->velocity.y * dt;

		// todo add missile explosion
		if (go->verticalPosition > SCREEN_HEIGHT - go->width) go->enabled = false;
	}

};
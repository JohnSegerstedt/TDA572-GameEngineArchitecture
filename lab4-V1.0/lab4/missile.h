#pragma once
#include "game_object.h"
#include "variables.h"


// The Red enemy missiles
class Missile : public GameObject {

	

public:

	Vector2D target;

	virtual void Init(double xPos, double yPos, double targetX, double targetY) {
		this->horizontalPosition = xPos;
		this->verticalPosition = yPos;
		Vector2D direction = (Vector2D(targetX, targetY).operator-(Vector2D(xPos, yPos))).normalize();
		this->velocity = direction * MISSILE_SPEED;
		this->orientation = atan2(direction.y, direction.x) * 180.0f / M_PI;
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
		go->horizontalPosition += go->velocity.x * dt;
		go->verticalPosition += go->velocity.y * dt;
	}

};
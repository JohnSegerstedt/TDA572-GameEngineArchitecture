#pragma once


#include "game_object.h"
class City : public GameObject {

public:
	bool alive;

	virtual void Init(double x, double y) {
		this->horizontalPosition = x;
		this->verticalPosition = y;
		enabled = true;
		alive = true;
	}

	virtual void Receive(Message m) {
		if (!enabled) return;

		if (m == HIT) {
			alive = false;
			Send(ALIEN_HIT); // todo
			SDL_Log("City::Hit");
		}
	}

};
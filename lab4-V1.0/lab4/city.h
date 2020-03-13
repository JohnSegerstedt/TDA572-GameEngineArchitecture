#pragma once

#include "game_object.h"
#include "graphics_system.h"

// A City object
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
			if(alive) Send(CITY_HIT);
			AudioSystem* audio_system;
			audio_system->getInstance()->PlaySound(CITY_DESTROYED);
			alive = false;
			collision = false;
		}
	}

};

class CityRenderComponent : public Component {
	Sprite* alive_city;
	Sprite* dead_city;

public:

	virtual void Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects, const char * alive_city, const char * dead_city, int width) {
		Component::Create(system, go, game_objects);

		GraphicsSystem* graphics_engine;
		this->alive_city = graphics_engine->getInstance()->createSprite(alive_city, width, width);
		this->dead_city = graphics_engine->getInstance()->createSprite(dead_city, width, width);
	}

	virtual void Update(float dt) {
		if (!go->enabled) return;
		Sprite* sprite = (((City*)go)->alive) ? alive_city : dead_city;
		if (sprite) sprite->draw(int(go->horizontalPosition), int(go->verticalPosition), 0);
	}

	Sprite * GetSprite() {
		return (((City*)go)->alive) ? alive_city : dead_city;
	}
};
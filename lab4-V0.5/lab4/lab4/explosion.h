#pragma once

#include "component.h"
#include "variables.h"
#include <algorithm>
#include <iostream>

/*
class ExplosionBehaviourComponent : public Component {

	float current_life = 0;
	float max_life = 5;

public:
	virtual void Update(float dt) {
		current_life += dt;
};*/

class ExplosionRenderComponent : public Component {
	Sprite* sprites[EXPLOSION_SPRITES];

	float current_life = 0;
	float max_life = 0.5;

public:

	virtual void Init() {
		current_life = 0;
	}

	virtual void Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects, std::set<const char *> new_sprites, int width) {
		Component::Create(system, go, game_objects);

		int index = 0;
		for (auto sprite = new_sprites.begin(); sprite != new_sprites.end(); sprite++)
			sprites[index++] = system->createSprite((*sprite), width, width);
	}

	virtual void Update(float dt) {
		if (!go->enabled) return;
		current_life += dt;
		if (current_life >= max_life) {
			go->enabled = false;
			return;
		}

		int index = std::min((int) (current_life * ((EXPLOSION_SPRITES) / max_life)), (int) (EXPLOSION_SPRITES - 1));
		Sprite* sprite = sprites[index];
		if (sprite) sprite->draw(int(go->horizontalPosition), int(go->verticalPosition), go->orientation);
	}


};




class Explosion : public GameObject {
public:
	virtual void Init(double xPos, double yPos, double orientation){
		GameObject::Init();

		horizontalPosition = xPos;
		verticalPosition = yPos;
		this->orientation = orientation;
	}


	virtual void Receive(Message m){
		if (m == HIT) {
		}
	}
};


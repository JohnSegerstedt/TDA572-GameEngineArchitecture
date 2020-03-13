#pragma once
#include "component.h"
#include "game_object.h"
#include "avancezlib.h"

void Component::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects) {
	this->go = go;
	this->system = system;
	this->game_objects = game_objects;
}

void RenderComponent::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects, const char * sprite_name) {
	Component::Create(system, go, game_objects);

	sprite = system->createSprite(sprite_name, go->radius * 2.0f, go->radius * 2.0f);
}

void RenderComponent::Update(float dt) {
	if (!go->enabled)
		return;

	if (sprite) sprite->draw(int(go->horizontalPosition), int(go->verticalPosition), int(go->orientation));
}

void RenderComponent::Destroy() {
	if (sprite != NULL)
		sprite->destroy();
	sprite = NULL;
}

void CollideComponent::Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, std::set<ObjectPool<GameObject>*> * colliders) {
	Component::Create(system, go, game_objects);
	this->colliders = colliders;
}


void CollideComponent::checkCollision(ObjectPool<GameObject> * colliders) {
	for (auto i = 0; i < colliders->pool.size(); i++) {
		GameObject * other = colliders->pool[i];
		if (other->enabled && other->radius != -1 && other->collision == true) {

			Vector2D thisPos = Vector2D(go->horizontalPosition, go->verticalPosition);
			Vector2D otherPos = Vector2D(other->horizontalPosition, other->verticalPosition);

			// circle vs circle
			if (thisPos.operator-(otherPos).length() < go->radius + other->radius) {
				go->Receive(HIT);
				other->Receive(HIT);
			}

			/*
			// box vs box
			if (abs(go->horizontalPosition - other->horizontalPosition) < go->width / 2.0f + other->width / 2.0f) {
				if (abs(go->verticalPosition - other->verticalPosition) < go->width / 2.0f + other->width / 2.0f) {
					go->Receive(HIT);
					other->Receive(HIT);
				}
			}*/
		}
	}
}

void CollideComponent::Update(float dt) {
	if (go->collision == false) return;
	for (auto collider = colliders->begin(); collider != colliders->end(); collider++) checkCollision(*collider);
}

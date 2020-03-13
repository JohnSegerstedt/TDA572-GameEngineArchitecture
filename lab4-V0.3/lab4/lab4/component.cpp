#pragma once
#include "component.h"
#include "game_object.h"
#include "avancezlib.h"

void Component::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects) {
	this->go = go;
	this->system = system;
	this->game_objects = game_objects;
}

void RenderComponent::Create(AvancezLib * system, GameObject * go, std::set<GameObject*>* game_objects, const char * sprite_name, int width, int height) {
	Component::Create(system, go, game_objects);

	sprite = system->createSprite(sprite_name, width, height);
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


void CollideComponent::Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<GameObject> * colliders) {
	Component::Create(system, go, game_objects);
	this->colliders = colliders;
}


void CollideComponent::Update(float dt) {
	for (auto i = 0; i < colliders->pool.size(); i++) {
		GameObject * other = colliders->pool[i];
		if (other->enabled && other->width != -1) {
			
			// box vs box
			if (abs(go->horizontalPosition - other->horizontalPosition) < go->width / 2.0f + other->width / 2.0f) {
				if (abs(go->verticalPosition - other->verticalPosition) < go->width / 2.0f + other->width / 2.0f) {
					go->Receive(HIT);
					other->Receive(HIT);
				}
			}
		}
	}
}

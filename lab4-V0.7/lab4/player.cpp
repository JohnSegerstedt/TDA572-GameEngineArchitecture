#pragma once

#include "player.h"
#include "time_handler.h"
#include "audio_handler.h"

void PlayerBehaviourComponent::Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, ObjectPool<Rocket> * rockets_pool, unsigned int* ammo_ptr) {
	Component::Create(system, go, game_objects);
	this->rockets_pool = rockets_pool;
	this->ammo = ammo_ptr;
}

void PlayerBehaviourComponent::Init() {
	std::cout << "TEST" << "\n";
	go->horizontalPosition = SCREEN_WIDTH / 2.0f;
	go->verticalPosition = SCREEN_HEIGHT / 2.0f;

	time_fire_pressed = -10000.f;
}

void PlayerBehaviourComponent::Fire() {
	if (CanFire() && *ammo > 0) {
		// fetches a rocket from the pool and use it in game_objects
		Rocket * rocket = rockets_pool->FirstAvailable();
		if (rocket != NULL) { // rocket is NULL is the object pool can not provide an object
			AudioHandler* audioHandler;
			audioHandler->getInstance()->PlaySound(ROCKET_SPAWNED);
			(*ammo)--;
			rocket->Init(go->horizontalPosition, go->verticalPosition);
			game_objects->insert(rocket);
		}
	}
}

void PlayerBehaviourComponent::Update(float dt) {

	AvancezLib::KeyStatus keys;
	system->getKeyStatus(keys);

	int speed = PLAYER_SPEED;
	if (keys.sprint) speed += PLAYER_SPEED;
	if (keys.right) MoveRelative(dt * speed, 0);
	if (keys.left) MoveRelative(-dt * speed, 0);
	if (keys.up) MoveRelative(0, -dt * speed);
	if (keys.down) MoveRelative(0, dt * speed);
	if (dt != 0 && keys.fire) Fire();
}


// move the player relative to its current position
// param move depends on the time, so the player moves always at the same speed on any computer
void PlayerBehaviourComponent::MoveRelative(float x, float y) {
	go->horizontalPosition += x;
	go->verticalPosition += y;

	// todo make more general
	if (go->horizontalPosition > (SCREEN_WIDTH - go->radius)) go->horizontalPosition = SCREEN_WIDTH - go->radius;
	if (go->horizontalPosition < go->radius) go->horizontalPosition = go->radius;
	if (go->verticalPosition > (SCREEN_HEIGHT - go->radius)) go->verticalPosition = SCREEN_HEIGHT - go->radius;
	if (go->verticalPosition < go->radius) go->verticalPosition = go->radius;
}

// return true if enough time has passed from the previous rocket
bool PlayerBehaviourComponent::CanFire() {
	// shoot just if enough time passed by
	TimeHandler* timeHandler;
	if ((system->getElapsedTime() - time_fire_pressed) < (FIRE_TIME_INTERVAL / timeHandler->getInstance()->getGameSpeed())) return false;
	time_fire_pressed = system->getElapsedTime();
	SDL_Log("fire!");
	return true;
}


void Player::Init() {
	GameObject::Init();
}

void Player::Receive(Message m) {}

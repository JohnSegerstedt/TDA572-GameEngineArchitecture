#pragma once

#include <vector>
#include "component.h"
#include "vector2D.h"
#include <set>

enum Message { HIT, ALIEN_HIT, GAME_OVER, LEVEL_WIN, NO_MSG }; // todo add more messages

class Component;

// GameObject represents objects which moves are drawn
class GameObject {
protected:
	std::vector<GameObject*> receivers;
	std::vector<Component*> components;

public:
	double horizontalPosition;
	double verticalPosition;
	Vector2D velocity;

	int width = 32;
	bool enabled;

	virtual ~GameObject();

	virtual void Create();
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	void Send(Message m);
	Component* getCollider();
};
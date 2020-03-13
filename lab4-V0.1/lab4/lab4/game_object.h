#pragma once

#include <vector>
#include "component.h"
#include <set>

enum Message { HIT, ALIEN_HIT, GAME_OVER, LEVEL_WIN, NO_MSG };

class Component;

// GameObject represents objects which moves are drawn
class GameObject {
protected:
	std::vector<GameObject*> receivers;
	std::vector<Component*> components;

public:
	double horizontalPosition;
	double verticalPosition;
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
};
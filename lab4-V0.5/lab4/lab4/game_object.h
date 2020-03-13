#pragma once

#include <vector>
#include "component.h"
#include "vector2D.h"
#include "variables.h"
#include <set>


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
	double orientation = 0;

	int radius = 16;
	bool enabled;

	bool collision = true;
	int depth = 1;

	virtual ~GameObject();

	virtual void Create(int depth);
	virtual void AddComponent(Component * component);

	virtual void Init();
	virtual void Update(float dt);
	virtual void Destroy();
	virtual void AddReceiver(GameObject *go);
	virtual void Receive(Message m) {}
	void Send(Message m);
	Component* getCollider();

	/*bool operator<(const GameObject& other) {
		return other.depth > depth;
	}*/

	/*
	struct game_object_compare{
		bool operator() (const GameObject *lhs, const GameObject *rhs) const {
			return true;
		}
	};*/

	/*struct comp {
		bool operator() (const int &lhs, const int &rhs) const {
			return true;
		}
	};*/
};

inline bool operator< (const GameObject& lhs, const GameObject& rhs) {
	return lhs.depth > rhs.depth;
}


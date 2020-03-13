#pragma once

#ifndef __COMPONENT__
#define __COMPONENT__

#include <set>
#include "object_pool.h"
#include "game_object.h"
#include "avancezlib.h"
#include "variables.h"

class GameObject;
class AvancezLib;
class Sprite;

// Following the Component design pattern
// Very similar to labs
class Component {

protected:
	AvancezLib * system;						// used to access the system
	GameObject * go;							// the game object this component is part of
	std::set<GameObject*> * game_objects;		// the global container of game objects
	//std::set<GameObject*, GameObject::game_object_compare> game_objects_new;

public:
	virtual ~Component() {}

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects);

	virtual void Init() {}
	virtual void Update(float dt) = 0;
	virtual void Receive(Message m) {}
	virtual void Destroy() {}
};


class RenderComponent : public Component {
	Sprite* sprite;

public:

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, const char * sprite_name);
	virtual void Update(float dt);
	virtual void Destroy();

	Sprite * GetSprite() { return sprite; }
};


class CollideComponent : public Component {
	std::set<ObjectPool<GameObject>*>* colliders; // collision will be tested with these objects

public:

	virtual void Create(AvancezLib* system, GameObject * go, std::set<GameObject*> * game_objects, std::set<ObjectPool<GameObject>*> * colliders);
	virtual void checkCollision(ObjectPool<GameObject> * colliders);
	virtual void Update(float dt);
};


#endif // __COMPONENT__
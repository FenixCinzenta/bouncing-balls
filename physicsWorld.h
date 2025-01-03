#pragma once
#include "objectsManager.h"
#include "SFML/Graphics.hpp"
#include <vector>

class PhysicsWorld {
private:
	objectManager* objManager;
	sf::RenderWindow* window;
	float gravity = 200;
	
	void check_object_collision_wall();

	void check_object_collision_object();

	void apply_gravity(float a, float dt);

	void move_objects(float dt);

public:
	PhysicsWorld(objectManager* o, sf::RenderWindow* w);

	void update(float dt);
};

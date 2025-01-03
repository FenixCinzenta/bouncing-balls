#pragma once

#include "SFML/Graphics.hpp"
#include <random>
#include <iostream>

class Object
{
private:
	sf::CircleShape image;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
	float damping;

public:
	Object();

	Object(sf::Vector2f pos);

	float getDamping();

	float getMass();

	sf::CircleShape& getSprite();

	sf::Vector2f getCenter();

	sf::Vector2f getVelocity();

	void setVelocity(sf::Vector2f vel);
};


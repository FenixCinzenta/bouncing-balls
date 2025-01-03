#include "object.h"

////public

Object::Object() {
	sf::Color color(rand() % 256, rand() % 256, rand() % 256, 255);
	image.setFillColor(color);
	image.setRadius(rand() % 40 + 20);

	image.setPosition(sf::Vector2f(100, 100));
	velocity.x = 0;
	velocity.y = 0;

	acceleration.x = 0;
	acceleration.y = 0;

	mass = image.getRadius() * 0.9f;
	damping = 0.8f;
}

Object::Object(sf::Vector2f pos) {
	sf::Color color(rand() % 256, rand() % 256, rand() % 256, 255);
	image.setFillColor(color);
	image.setRadius(rand() % 40 + 20);

	image.setPosition(pos);
	velocity.x = 0;
	velocity.y = 0;

	acceleration.x = 0;
	acceleration.y = 0;

	mass = image.getRadius() * 0.9f;
	damping = 0.7f;
}

float Object::getDamping() {
	return damping;
}

float Object::getMass() {
	return mass;
}

sf::CircleShape& Object::getSprite() {
	return image;
}

sf::Vector2f Object::getCenter() {
	return sf::Vector2f(image.getPosition().x + image.getRadius(), image.getPosition().y + image.getRadius());
}

sf::Vector2f Object::getVelocity() {
	return velocity;
}

void Object::setVelocity(sf::Vector2f vel) {
	velocity = vel;
}

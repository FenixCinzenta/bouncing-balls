#include "objectsManager.h"

objectManager::objectManager(sf::RenderWindow* w) {
	window = w;
}

void objectManager::insert_object(const Object& o) {
	objects_v.push_back(o);
}

void objectManager::create_object() {
	Object o;
	objects_v.push_back(o);
}

void objectManager::create_object(sf::Vector2f pos) {
	Object o(pos);
	objects_v.push_back(o);
}

////public

void objectManager::render_objects() {
	for (int i = 0; i < objects_v.size(); i++) {
		window->draw(objects_v[i].getSprite());
	}
}

std::vector<Object>& objectManager::getObjects() {
	return objects_v;
}

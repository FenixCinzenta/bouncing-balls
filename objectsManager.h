#pragma once
#include "object.h"
#include "SFML/Graphics.hpp"
#include <vector>

class objectManager {
private:
	std::vector<Object> objects_v;
	sf::RenderWindow* window;

public:

	objectManager(sf::RenderWindow* w);
	
	void insert_object(const Object& o);

	void create_object();

	void create_object(sf::Vector2f pos);

	void render_objects();

	std::vector<Object>& getObjects();
};

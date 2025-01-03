#include <iostream>
#include "SFML/Graphics.hpp"
#include "object.h"
#include "objectsManager.h"
#include "physicsWorld.h"


int main() {

	sf::RenderWindow window(sf::VideoMode(800, 800), "Janela");
	objectManager objManager(&window);
	PhysicsWorld world(&objManager, &window);
	sf::Clock clock;
	
	srand(time(NULL));

	while (window.isOpen()) {
		sf::Event event;
		float dt = clock.restart().asSeconds();
		std::cout << dt << std::endl;

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {

				sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

				objManager.create_object(sf::Vector2f(mouse_pos.x, mouse_pos.y));
			}
		}

		world.update(dt);
		objManager.render_objects();
		window.display();
		window.clear();

	}

	return 0;
}

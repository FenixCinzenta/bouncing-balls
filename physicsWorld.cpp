#include "physicsWorld.h"

void PhysicsWorld::check_object_collision_wall() {
	std::vector<Object>& objects_v = objManager->getObjects();

	for (int i = 0; i < objects_v.size(); i++) {
		float overlap;

		float pos_x = objects_v[i].getSprite().getPosition().x;
		float pos_y = objects_v[i].getSprite().getPosition().y;

		float radius = objects_v[i].getSprite().getRadius();

		float vel_x = objects_v[i].getVelocity().x;
		float vel_y = objects_v[i].getVelocity().y;

		if (pos_x <= 0) {
			objects_v[i].setVelocity(sf::Vector2f(vel_x * -1 * objects_v[i].getDamping(), vel_y));

			objects_v[i].getSprite().setPosition(0, pos_y);
		}

		if (pos_x + 2 * radius >= window->getSize().x) {
			objects_v[i].setVelocity(sf::Vector2f(vel_x * -1 * objects_v[i].getDamping(), vel_y));

			objects_v[i].getSprite().setPosition(window->getSize().x - 2 * radius, pos_y);
		}

		if (pos_y + 2 * radius >= window->getSize().y) {
			objects_v[i].setVelocity(sf::Vector2f(vel_x, vel_y * -1 * objects_v[i].getDamping()));

			objects_v[i].getSprite().setPosition(pos_x, window->getSize().y - 2 * radius);
		}

		if (pos_y <= 0) {
			objects_v[i].setVelocity(sf::Vector2f(vel_x, vel_y * -1 * objects_v[i].getDamping()));

			objects_v[i].getSprite().setPosition(pos_x, 0);
		}
	}
}

void PhysicsWorld::check_object_collision_object() {
	std::vector<Object>& objects_v = objManager->getObjects();

	for (int i = 0; i < objects_v.size(); i++) {
		for (int j = i + 1; j < objects_v.size(); j++) {

			float radius_i = objects_v[i].getSprite().getRadius();
			float radius_j = objects_v[j].getSprite().getRadius();

			sf::Vector2f velocity_i = objects_v[i].getVelocity();
			sf::Vector2f velocity_j = objects_v[j].getVelocity();
			sf::Vector2f pos_i = objects_v[i].getSprite().getPosition();
			sf::Vector2f pos_j = objects_v[j].getSprite().getPosition();

			sf::Vector2f center_i = objects_v[i].getCenter();
			sf::Vector2f center_j = objects_v[j].getCenter();

			sf::Vector2f delta = center_i - center_j;
			float distance = std::sqrt((delta.x * delta.x) + (delta.y * delta.y));

			if (distance < (radius_i + radius_j)) {

				sf::Vector2f normal_vector = pos_i - pos_j;
				float length_normal = std::sqrt(normal_vector.x * normal_vector.x + normal_vector.y * normal_vector.y);
				normal_vector = normal_vector / length_normal;

				float overlap = (radius_i + radius_j) - distance;

				sf::Vector2f displacement_i = normal_vector * (overlap * (radius_j / (radius_i + radius_j)));
				sf::Vector2f displacement_j = normal_vector * (overlap * (radius_i / (radius_i + radius_j)));

				objects_v[i].getSprite().setPosition(pos_i + displacement_i);
				objects_v[j].getSprite().setPosition(pos_j - displacement_j);

				sf::Vector2f tangent_vector(-normal_vector.y, normal_vector.x);

				float vin = velocity_i.x * normal_vector.x + velocity_i.y * normal_vector.y;
				float vit = velocity_i.x * tangent_vector.x + velocity_i.y * tangent_vector.y;

				float vjn = velocity_j.x * normal_vector.x + velocity_j.y * normal_vector.y;
				float vjt = velocity_j.x * tangent_vector.x + velocity_j.y * tangent_vector.y;

				float mass_i = objects_v[i].getMass();
				float mass_j = objects_v[j].getMass();

				float new_vin = (vin * (mass_i - mass_j) + 2 * mass_j * vjn) / (mass_i + mass_j);
				float new_vjn = (vjn * (mass_j - mass_i) + 2 * mass_i * vin) / (mass_i + mass_j);

				sf::Vector2f new_velocity_i(vit * tangent_vector.x + new_vin * normal_vector.x, vit * tangent_vector.y + new_vin * normal_vector.y);
				sf::Vector2f new_velocity_j(vjt * tangent_vector.x + new_vjn * normal_vector.x, vjt * tangent_vector.y + new_vjn * normal_vector.y);

				objects_v[i].setVelocity(new_velocity_i);
				objects_v[j].setVelocity(new_velocity_j);
			}
		}
	}

}

void PhysicsWorld::apply_gravity(float a, float dt) {
	std::vector<Object>& objects_v = objManager->getObjects();

	for (int i = 0; i < objects_v.size(); i++) {
		sf::Vector2f new_velocity(objects_v[i].getVelocity().x, objects_v[i].getVelocity().y + a * dt);
		objects_v[i].setVelocity(new_velocity);
	}
}

void PhysicsWorld::move_objects(float dt) {
	std::vector<Object>& objects_v = objManager->getObjects();

	for (int i = 0; i < objects_v.size(); i++) {
		sf::Vector2f offset(objects_v[i].getVelocity().x * dt, objects_v[i].getVelocity().y * dt);
		objects_v[i].getSprite().move(offset);
	}
}

////public

PhysicsWorld::PhysicsWorld(objectManager* o, sf::RenderWindow* w) {
	objManager = o;
	window = w;
}

void PhysicsWorld::update(float dt) {
	check_object_collision_wall();
	check_object_collision_object();
	apply_gravity(gravity, dt);
	move_objects(dt);
}

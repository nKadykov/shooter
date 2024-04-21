#include "healthbar.h"

HealthBar::HealthBar(int healthX, int healthY, sf::Sprite sprite) {
	position_x = healthX;
	position_y = healthY;
	health_point_sprite = sprite;
	for (int i = 0; i < health; i++) {
		HealthPoint newHealthPoint(healthX, healthY, sprite);
		health_bar_vector.push_back(newHealthPoint);
		healthX += 40;
	}
}

void HealthBar::decreaseHealth() {
	health--;
	if (health > 0) {
		health_bar_vector.pop_back();
	}
}

void HealthBar::setHealth(int playerHealth) {
	health = playerHealth;
	health_bar_vector.clear();
	int healthX = position_x;
	int healthY = position_y;
	for (int i = 0; i < health; i++) {
		HealthPoint newHealthPoint(healthX, healthY, health_point_sprite);
		health_bar_vector.push_back(newHealthPoint);
		healthX += 40;
	}
}

void HealthBar::draw(sf::RenderWindow& window) {
	for (int i = 0; i < health; i++) {
		window.draw(health_bar_vector[i].getHealthPointSprite());
	}
}
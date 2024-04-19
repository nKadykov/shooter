#include "HealthBar.h"

HealthBar::HealthBar(int healthX, int healthY, sf::Sprite sprite) {
	positionX = healthX;
	positionY = healthY;
	healthPointSprite = sprite;
	for (int i = 0; i < health; i++) {
		HealthPoint newHealthPoint(healthX, healthY, sprite);
		healthBarVector.push_back(newHealthPoint);
		healthX += 40;
	}
}

void HealthBar::decreaseHealth() {
	health--;
	if (health > 0) {
		healthBarVector.pop_back();
	}
}

void HealthBar::setHealth(int playerHealth) {
	health = playerHealth;
	healthBarVector.clear();
	int healthX = positionX;
	int healthY = positionY;
	for (int i = 0; i < health; i++) {
		HealthPoint newHealthPoint(healthX, healthY, healthPointSprite);
		healthBarVector.push_back(newHealthPoint);
		healthX += 40;
	}
}

void HealthBar::draw(sf::RenderWindow& window) {
	for (int i = 0; i < health; i++) {
		window.draw(healthBarVector[i].getHealthPointSprite());
	}
}
#include "HealthPoint.h"

HealthPoint::HealthPoint(int healthPointX, int healthPointY, sf::Sprite sprite) {
	healthPointPosition.x = healthPointX;
	healthPointPosition.y = healthPointY;

	healthPointSprite = sprite;
	healthPointSprite.setPosition(healthPointPosition);
}

sf::Sprite HealthPoint::getHealthPointSprite() {
	return healthPointSprite;
}

sf::FloatRect HealthPoint::getHealthPointPosition() {
	return healthPointSprite.getGlobalBounds();
}
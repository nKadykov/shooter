#include "healthpoint.h"

HealthPoint::HealthPoint(int healthPointX, int healthPointY, sf::Sprite sprite) {
	healthPointPosition.x = healthPointX;
	healthPointPosition.y = healthPointY;

	health_point_sprite = sprite;
	health_point_sprite.setPosition(healthPointPosition);
}

sf::Sprite HealthPoint::getHealthPointSprite() {
	return health_point_sprite;
}

sf::FloatRect HealthPoint::getHealthPointPosition() {
	return health_point_sprite.getGlobalBounds();
}
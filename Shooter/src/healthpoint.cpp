#include "healthpoint.h"

HealthPoint::HealthPoint(int healthPointX, int healthPointY, sf::Sprite sprite) {
	m_health_point_position.x = healthPointX;
	m_health_point_position.y = healthPointY;

	m_health_point_sprite = sprite;
	m_health_point_sprite.setPosition(m_health_point_position);
}

sf::Sprite HealthPoint::getHealthPointSprite() {
	return m_health_point_sprite;
}

sf::FloatRect HealthPoint::getHealthPointPosition() {
	return m_health_point_sprite.getGlobalBounds();
}
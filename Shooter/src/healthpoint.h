#pragma once
#include <SFML/Graphics.hpp>

class HealthPoint
{
private:
	sf::CircleShape m_health_point_shape;
	sf::Vector2f m_health_point_position;
	sf::Sprite m_health_point_sprite;
public:
	HealthPoint() = delete;
	HealthPoint(int healthPointX, int healthPointY, sf::Sprite);
	HealthPoint(const HealthPoint&) = default;
	HealthPoint(HealthPoint&&) = default;
	HealthPoint& operator=(const HealthPoint&) = default;
	HealthPoint& operator=(HealthPoint&&) = default;

	sf::Sprite getHealthPointSprite();
	sf::FloatRect getHealthPointPosition();
};
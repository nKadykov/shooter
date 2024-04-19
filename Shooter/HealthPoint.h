#pragma once
#include <SFML/Graphics.hpp>

class HealthPoint
{
private:
	sf::CircleShape healthPointShape;
	sf::Vector2f healthPointPosition;
	sf::Sprite healthPointSprite;
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
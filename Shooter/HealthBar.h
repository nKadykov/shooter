#pragma once
#include <SFML/Graphics.hpp>
#include "HealthPoint.h"
#include <vector>

class HealthBar
{
	int positionX;
	int positionY;
	sf::Sprite healthPointSprite;
	std::vector<HealthPoint> healthBarVector;
	int health = 5;
	bool isAlive = true;

public:
	HealthBar() = delete;
	HealthBar(int, int, sf::Sprite);
	HealthBar(const HealthBar&) = delete;
	HealthBar(HealthBar&&) = delete;
	HealthBar& operator=(const HealthBar&) = delete;
	HealthBar& operator=(HealthBar&&) = delete;
	~HealthBar() = default;

	void setHealth(int);
	void decreaseHealth();
	void draw(sf::RenderWindow&);
};
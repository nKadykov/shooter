#pragma once
#include <SFML/Graphics.hpp>
#include "HealthPoint.h"
#include <vector>

class HealthBar
{
	int position_x;
	int position_y;
	sf::Sprite health_point_sprite;
	std::vector<HealthPoint> health_bar_vector;
	int health = 5;
	bool is_alive = true;

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
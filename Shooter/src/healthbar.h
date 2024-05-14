#pragma once
#include <SFML/Graphics.hpp>
#include "HealthPoint.h"
#include <vector>

class HealthBar
{
	int m_position_x;
	int m_position_y;
	sf::Sprite m_health_point_sprite;
	std::vector<HealthPoint> m_health_bar_vector;
	int m_health = 5;
	bool m_is_alive = true;

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
	void draw(std::unique_ptr<sf::RenderWindow>&);
};
#include "healthbar.h"

HealthBar::HealthBar(int healthX, int healthY, sf::Sprite sprite) {
	m_position_x = healthX;
	m_position_y = healthY;
	m_health_point_sprite = sprite;
	for (int i = 0; i < m_health; i++) {
		HealthPoint newHealthPoint(healthX, healthY, sprite);
		m_health_bar_vector.push_back(newHealthPoint);
		healthX += 40;
	}
}

void HealthBar::decreaseHealth() {
	m_health--;
	if (m_health > 0) {
		m_health_bar_vector.pop_back();
	}
}

void HealthBar::setHealth(int playerHealth) {
	m_health = playerHealth;
	m_health_bar_vector.clear();
	int healthX = m_position_x;
	int healthY = m_position_y;
	for (int i = 0; i < m_health; i++) {
		HealthPoint newHealthPoint(healthX, healthY, m_health_point_sprite);
		m_health_bar_vector.push_back(newHealthPoint);
		healthX += 40;
	}
}

void HealthBar::draw(std::unique_ptr<sf::RenderWindow>& window) {
	for (int i = 0; i < m_health; i++) {
		window->draw(m_health_bar_vector[i].getHealthPointSprite());
	}
}
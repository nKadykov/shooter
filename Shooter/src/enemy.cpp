#include "enemy.h"

Enemy::Enemy(int startX, int startY, const sf::Sprite& sprite) {
	m_enemy_speed = 500.0f;
	m_enemy_position.x = startX;
	m_enemy_position.y = startY;

	m_enemy_sprite = sprite;
	m_enemy_sprite.setPosition(m_enemy_position);
}

sf::FloatRect Enemy::getPosition() {
	return m_enemy_sprite.getGlobalBounds();
}

int Enemy::getX() const {
	return m_enemy_position.x;
}

void Enemy::getHit() {
	m_enemy_hit = true;
}

bool Enemy::ifHitted() const {
	return m_enemy_hit;
}

void Enemy::draw(std::unique_ptr<sf::RenderWindow>& window) const {
	window->draw(m_enemy_sprite);
}

void Enemy::update(const sf::Time& dt) {
	m_enemy_position.x -= m_enemy_speed * dt.asSeconds();
	m_enemy_sprite.setPosition(m_enemy_position);
}
#include "enemy.h"

Enemy::Enemy(int startX, int startY, sf::Sprite sprite) {
	enemy_speed = 500.0f;
	enemy_position.x = startX;
	enemy_position.y = startY;

	enemy_sprite = sprite;
	enemy_sprite.setPosition(enemy_position);
}

sf::FloatRect Enemy::getPosition() {
	return enemy_sprite.getGlobalBounds();
}

int Enemy::getX() const {
	return enemy_position.x;
}

void Enemy::getHit() {
	enemy_hit = true;
}

bool Enemy::ifHitted() const {
	return enemy_hit;
}

void Enemy::draw(sf::RenderWindow& window) const {
	window.draw(enemy_sprite);
}

void Enemy::update(sf::Time dt) {
	enemy_position.x -= enemy_speed * dt.asSeconds();
	enemy_sprite.setPosition(enemy_position);
}
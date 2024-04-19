#include "Enemy.h"

Enemy::Enemy(int startX, int startY, sf::Sprite sprite) {
	enemyPosition.x = startX;
	enemyPosition.y = startY;

	enemySprite = sprite;
	enemySprite.setPosition(enemyPosition);
}

sf::FloatRect Enemy::getPosition() {
	return enemySprite.getGlobalBounds();
}

int Enemy::getX() {
	return enemyPosition.x;
}

void Enemy::getHit() {
	enemyHitted = true;
}

bool Enemy::ifHitted() const {
	return enemyHitted;
}

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(enemySprite);
}

void Enemy::update(sf::Time dt) {
	enemyPosition.x -= enemySpeed * dt.asSeconds();
	enemySprite.setPosition(enemyPosition);
}
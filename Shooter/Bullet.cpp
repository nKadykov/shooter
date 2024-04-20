#include "bullet.h"

Bullet::Bullet(int startX, int startY) {
	bulletPosition.x = startX;
	bulletPosition.y = startY;

	bulletShape.setRadius(5);
	bulletShape.setFillColor(sf::Color::White);
	bulletShape.setOutlineColor(sf::Color::Blue);
	bulletShape.setOutlineThickness(2);
	bulletShape.setPosition(bulletPosition);
}

sf::CircleShape Bullet::getShape() {
	return bulletShape;
}

sf::FloatRect Bullet::getPosition() {
	return bulletShape.getGlobalBounds();
}

int Bullet::getX() {
	return bulletPosition.x;
}

void Bullet::makeHit() {
	madeHit = true;
}

bool Bullet::ifMadeHit() const {
	return (madeHit == true) ? true : false;
}

void Bullet::drawBullet(sf::RenderWindow& window) const {
	window.draw(bulletShape);
}

void Bullet::update(sf::Time dt) {
	bulletPosition.x += bulletSpeed * dt.asSeconds();
	bulletShape.setPosition(bulletPosition);
}
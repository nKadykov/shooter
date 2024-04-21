#include "bullet.h"

Bullet::Bullet(int startX, int startY) {
	bullet_position.x = startX;
	bullet_position.y = startY;

	bullet_shape.setRadius(5);
	bullet_shape.setFillColor(sf::Color::White);
	bullet_shape.setOutlineColor(sf::Color::Blue);
	bullet_shape.setOutlineThickness(2);
	bullet_shape.setPosition(bullet_position);
}

sf::CircleShape Bullet::getShape() {
	return bullet_shape;
}

sf::FloatRect Bullet::getPosition() {
	return bullet_shape.getGlobalBounds();
}

int Bullet::getX() {
	return bullet_position.x;
}

void Bullet::makeHit() {
	made_hit = true;
}

bool Bullet::ifMadeHit() const {
	return (made_hit == true) ? true : false;
}

void Bullet::drawBullet(sf::RenderWindow& window) const {
	window.draw(bullet_shape);
}

void Bullet::update(sf::Time dt) {
	bullet_position.x += bullet_speed * dt.asSeconds();
	bullet_shape.setPosition(bullet_position);
}
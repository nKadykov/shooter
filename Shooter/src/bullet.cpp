#include "bullet.h"

Bullet::Bullet(int startX, int startY) {
	m_bullet_position.x = startX;
	m_bullet_position.y = startY;

	m_bullet_shape.setRadius(5);
	m_bullet_shape.setFillColor(sf::Color::White);
	m_bullet_shape.setOutlineColor(sf::Color::Blue);
	m_bullet_shape.setOutlineThickness(2);
	m_bullet_shape.setPosition(m_bullet_position);
}

sf::CircleShape Bullet::getShape() {
	return m_bullet_shape;
}

sf::FloatRect Bullet::getPosition() {
	return m_bullet_shape.getGlobalBounds();
}

int Bullet::getX() {
	return m_bullet_position.x;
}

void Bullet::makeHit() {
	m_made_hit = true;
}

bool Bullet::ifMadeHit() const {
	return (m_made_hit == true) ? true : false;
}

void Bullet::drawBullet(std::unique_ptr<sf::RenderWindow>& window) const {
	window->draw(m_bullet_shape);
}

void Bullet::update(const sf::Time& dt) {
	m_bullet_position.x += m_bullet_speed * dt.asSeconds();
	m_bullet_shape.setPosition(m_bullet_position);
}
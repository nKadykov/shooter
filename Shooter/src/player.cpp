#include "player.h"

Player::Player(float startX, float startY, const sf::Sprite& sprite) {
	m_player_position.x = startX;
	m_player_position.y = startY;

	if (!m_player_texture.loadFromFile("images/player1.png")) {
		exit(1);
	}

	m_player_sprite = sprite;
}


sf::FloatRect Player::getPosition() {
	return m_player_sprite.getGlobalBounds();
}

int Player::getHealth() {
	return m_player_health;
}

void Player::moveDown() {
	m_player_moving_down = true;
}

void Player::moveUp() {
	m_player_moving_up = true;
}

void Player::stopDown() {
	m_player_moving_down = false;
}

void Player::stopUp() {
	m_player_moving_up = false;
}

void Player::decreaseHealth() {
	m_player_health--;
}

bool Player::ifAlive() const {
	if (m_player_health > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Player::draw(std::unique_ptr<sf::RenderWindow>& window) const {
	window->draw(m_player_sprite);
}

void Player::update(const sf::Time& dt) {
	if (m_player_moving_down) {
		m_player_position.y += m_player_speed * dt.asSeconds();
	}
	if (m_player_moving_up) {
		m_player_position.y -= m_player_speed * dt.asSeconds();
	}
	if (m_player_position.y > 630) {
		m_player_position.y = 630;
	}
	if (m_player_position.y < 60) {
		m_player_position.y = 60;
	}
	m_player_sprite.setPosition(m_player_position);
}
#include "player.h"

Player::Player(float startX, float startY, sf::Sprite sprite) {
	player_position.x = startX;
	player_position.y = startY;

	if (!player_texture.loadFromFile("resources/player1.png")) {
		exit(1);
	}

	player_sprite = sprite;
}


sf::FloatRect Player::getPosition() {
	return player_sprite.getGlobalBounds();
}

int Player::getHealth() {
	return player_health;
}

void Player::moveDown() {
	player_moving_down = true;
}

void Player::moveUp() {
	player_moving_up = true;
}

void Player::stopDown() {
	player_moving_down = false;
}

void Player::stopUp() {
	player_moving_up = false;
}

void Player::decreaseHealth() {
	player_health--;
}

bool Player::ifAlive() const {
	if (player_health > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Player::draw(sf::RenderWindow& window) const {
	window.draw(player_sprite);
}

void Player::update(sf::Time dt) {
	if (player_moving_down) {
		player_position.y += player_speed * dt.asSeconds();
	}
	if (player_moving_up) {
		player_position.y -= player_speed * dt.asSeconds();
	}
	if (player_position.y > 650) {
		player_position.y = 650;
	}
	if (player_position.y < 60) {
		player_position.y = 60;
	}
	player_sprite.setPosition(player_position);
}
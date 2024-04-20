#include "player.h"

Player::Player(float startX, float startY, sf::Sprite sprite) {
	playerPosition.x = startX;
	playerPosition.y = startY;

	if (!playerTexture.loadFromFile("resources/player1.png")) {
		exit(1);
	}

	playerSprite = sprite;
}


sf::FloatRect Player::getPosition() {
	return playerSprite.getGlobalBounds();
}

int Player::getHealth() {
	return playerHealth;
}

void Player::moveDown() {
	playerMovingDown = true;
}

void Player::moveUp() {
	playerMovingUp = true;
}

void Player::stopDown() {
	playerMovingDown = false;
}

void Player::stopUp() {
	playerMovingUp = false;
}

void Player::decreaseHealth() {
	playerHealth--;
}

bool Player::ifAlive() const {
	if (playerHealth > 0) {
		return true;
	}
	else {
		return false;
	}
}

void Player::draw(sf::RenderWindow& window) const {
	window.draw(playerSprite);
}

void Player::update(sf::Time dt) {
	if (playerMovingDown) {
		playerPosition.y += playerSpeed * dt.asSeconds();
	}
	if (playerMovingUp) {
		playerPosition.y -= playerSpeed * dt.asSeconds();
	}
	if (playerPosition.y > 650) {
		playerPosition.y = 650;
	}
	if (playerPosition.y < 60) {
		playerPosition.y = 60;
	}
	playerSprite.setPosition(playerPosition);
}
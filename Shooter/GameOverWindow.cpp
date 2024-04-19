#include "GameOverWindow.h"

GameOverWindow::GameOverWindow() {
	gameOverTexture.loadFromFile("resources/GameOver.jpg");
	gameOverSprite.setTexture(gameOverTexture);
	backgroundTexture.loadFromFile("resources/back1.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	buttonTexture.loadFromFile("resources/Again.png");
	buttonSprite.setTexture(buttonTexture);
}

void GameOverWindow::setPosition(float positionX, float positionY) {
	gameOverSprite.setPosition(positionX, positionY);
	buttonSprite.setPosition(230, 300);
}

GameOverState GameOverWindow::getState() {
	return gameOverState;
}

void GameOverWindow::setState(GameOverState state) {
	gameOverState = state;
}

void GameOverWindow::draw(sf::RenderWindow& window) {
	gameOverState = GameOverState::on;
	window.clear();
	if ((sf::Mouse::getPosition(window).x < 900) && (sf::Mouse::getPosition(window).x > 400) && (sf::Mouse::getPosition(window).y > 400) && (sf::Mouse::getPosition(window).y < 500)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			gameOverState = GameOverState::off;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		gameOverState = GameOverState::menu;
	}
	window.draw(backgroundSprite);
	window.draw(gameOverSprite);
	window.draw(buttonSprite);
}
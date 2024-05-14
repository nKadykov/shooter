#include "gameoverwindow.h"

GameOverWindow::GameOverWindow() {
	m_state = GameOverState::ON;
	m_texture.loadFromFile("images/GameOver.jpg");
	m_sprite.setTexture(m_texture);
	m_background_texture.loadFromFile("images/back1.jpg");
	m_background_sprite.setTexture(m_background_texture);
	m_button_texture.loadFromFile("images/Again.png");
	m_button_sprite.setTexture(m_button_texture);
}

void GameOverWindow::setPosition(float positionX, float positionY) {
	m_sprite.setPosition(positionX, positionY);
	m_button_sprite.setPosition(230, 300);
}

GameOverState GameOverWindow::getState() {
	return m_state;
}

void GameOverWindow::setState(GameOverState state) {
	m_state = state;
}

void GameOverWindow::draw(std::unique_ptr<sf::RenderWindow>& window) {
	m_state = GameOverState::ON;
	window->clear();

	Button button(230, 300, m_button_texture);
	if (button.isPushed(window)) {
		m_state = GameOverState::OFF;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		m_state = GameOverState::MENU;
	}

	window->draw(m_background_sprite);
	window->draw(m_sprite);
	button.draw(window);
}
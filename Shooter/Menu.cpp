#include "menu.h"

Menu::Menu() {
	buttonState = ButtonState::NONE;
	menuTexture.loadFromFile("resources/back1.jpg");
	menuSprite.setTexture(menuTexture);
}

Menu::Menu(std::string filename) {
	buttonState = ButtonState::NONE;
	menuTexture.loadFromFile(filename);
	menuSprite.setTexture(menuTexture);
}

Menu::~Menu() {
	for (auto it = buttonVector.begin(); it != buttonVector.end(); it++) {
		delete* it;
	}
}

void Menu::addButton(int buttonX, int buttonY, std::string filename) {
	Button* newButton = new Button(buttonX, buttonY, filename);
	buttonVector.push_back(newButton);
}

ButtonState Menu::getButtonState() {
	return buttonState;
}

MenuState Menu::getState() {
	return menuState;
}

void Menu::setButtonState(ButtonState state) {
	buttonState = state;
}

void Menu::setState(MenuState state) {
	menuState = state;
}

void Menu::draw(sf::RenderWindow& window) {
	window.clear();
	buttonState = NONE;
	if ((sf::Mouse::getPosition(window).x < 700) && (sf::Mouse::getPosition(window).x > 500) && (sf::Mouse::getPosition(window).y > 200) && (sf::Mouse::getPosition(window).y < 300)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = ButtonState::START_GAME;
		}
	}
	if ((sf::Mouse::getPosition(window).x < 700) && (sf::Mouse::getPosition(window).x > 500) && (sf::Mouse::getPosition(window).y > 400) && (sf::Mouse::getPosition(window).y < 500)) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			buttonState = ButtonState::CLOSE;
		}
	}
	window.draw(menuSprite);
	for (auto it = buttonVector.begin(); it != buttonVector.end(); it++) {
		(*it)->draw(window);
	}
}
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"

enum class MenuState { on, off };
enum ButtonState { none, button1, button2 };

class Menu
{
private:
	std::vector<Button*> buttonVector;
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	ButtonState buttonState;
	MenuState menuState;
public:
	Menu();
	Menu(std::string);
	Menu(const Menu&) = delete;
	Menu(Menu&&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu& operator=(Menu&&) = delete;
	~Menu();

	ButtonState getButtonState();
	MenuState getState();
	void setButtonState(ButtonState state);
	void setState(MenuState state);
	void addButton(int, int, std::string);
	void draw(sf::RenderWindow&);
};

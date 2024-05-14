#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "button.h"

enum class MenuState { ON, OFF };
enum ButtonState { NONE, START_GAME, CLOSE };

class Menu
{
private:
	std::vector<std::unique_ptr<Button>> m_button_vector;
	sf::Texture m_menu_texture;
	sf::Sprite m_menu_sprite;
	ButtonState m_button_state;
	MenuState m_menu_state;
public:
	Menu();
	Menu(const std::string&);
	Menu(const Menu&) = delete;
	Menu(Menu&&) = delete;
	Menu& operator=(const Menu&) = delete;
	Menu& operator=(Menu&&) = delete;
	~Menu() = default;

	ButtonState getButtonState() const;
	MenuState getState() const;
	void setButtonState(ButtonState);
	void setState(MenuState);
	void addButton(int, int, const sf::Texture&);
	void draw(std::unique_ptr<sf::RenderWindow>&);
};
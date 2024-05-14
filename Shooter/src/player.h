#pragma once
#include <SFML/graphics.hpp>

class Player
{
private:
	sf::Vector2f m_player_position;
	sf::Texture m_player_texture;
	sf::Sprite m_player_sprite;
	float m_player_speed = 700.0f;
	bool m_player_moving_down = false;
	bool m_player_moving_up = false;
	int m_player_health = 4;
	bool m_is_alive = true;

public:
	Player() = delete;
	Player(float startX, float startY, const sf::Sprite&);
	Player(const Player&) = delete;
	Player(Player&&) = delete;
	Player& operator=(const Player&) = delete;
	Player& operator=(Player&&) = delete;

	sf::FloatRect getPosition();
	int getHealth();
	void moveDown();
	void moveUp();
	void stopDown();
	void stopUp();
	void decreaseHealth();
	bool ifAlive() const;
	void draw(std::unique_ptr<sf::RenderWindow>&) const;
	void update(const sf::Time& dt);
};

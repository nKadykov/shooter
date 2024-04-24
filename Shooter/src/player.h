#pragma once
#include <SFML/graphics.hpp>

class Player
{
private:
	sf::Vector2f player_position;
	sf::Texture player_texture;
	sf::Sprite player_sprite;
	float player_speed = 700.0f;
	bool player_moving_down = false;
	bool player_moving_up = false;
	int player_health = 4;
	bool is_alive = true;

public:
	Player() = delete;
	Player(float startX, float startY, sf::Sprite);
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
	void draw(sf::RenderWindow&) const;
	void update(sf::Time dt);
};

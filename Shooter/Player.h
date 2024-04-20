#pragma once
#include <SFML/graphics.hpp>

class Player
{
private:
	sf::Vector2f playerPosition;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	float playerSpeed = 700.0f;
	bool playerMovingDown = false;
	bool playerMovingUp = false;
	int playerHealth = 4;
	bool isAlive = true;

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
	void drawPlayer(sf::RenderWindow&);
	void update(sf::Time dt);
};

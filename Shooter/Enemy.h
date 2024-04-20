#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Vector2f enemyPosition;
	sf::Sprite enemySprite;
	float enemySpeed;
	bool enemyHitted = false;
public:
	Enemy() = delete;
	Enemy(int startX, int startY, sf::Sprite);
	Enemy(const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(const Enemy&) = delete;
	Enemy& operator=(Enemy&&) = delete;
	~Enemy() = default;

	sf::FloatRect getPosition();
	int getX();
	void getHit();
	bool ifHitted() const;

	void draw(sf::RenderWindow&) const;
	void update(sf::Time);
};
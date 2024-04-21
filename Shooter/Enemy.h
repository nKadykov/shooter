#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Vector2f enemy_position;
	sf::Sprite enemy_sprite;
	float enemy_speed;
	bool enemy_hit = false;
public:
	Enemy() = delete;
	Enemy(int startX, int startY, sf::Sprite);
	Enemy(const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(const Enemy&) = delete;
	Enemy& operator=(Enemy&&) = delete;
	~Enemy() = default;

	sf::FloatRect getPosition();
	int getX() const;
	void getHit();
	bool ifHitted() const;

	void draw(sf::RenderWindow&) const;
	void update(sf::Time);
};
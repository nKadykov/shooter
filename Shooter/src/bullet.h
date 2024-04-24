#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::CircleShape bullet_shape;
	sf::Vector2f bullet_position;
	float bullet_speed = 1000.0f;
	bool made_hit = false;
public:
	Bullet() = delete;
	Bullet(int startX, int startY);
	Bullet(const Bullet&) = default;
	Bullet(Bullet&&) = default;
	Bullet& operator=(const Bullet&) = delete;
	Bullet& operator=(Bullet&&) = delete;
	~Bullet() = default;

	sf::CircleShape getShape();
	sf::FloatRect getPosition();
	int getX();

	void makeHit();
	bool ifMadeHit() const;

	void drawBullet(sf::RenderWindow&) const;
	void update(sf::Time dt);
};
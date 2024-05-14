#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	sf::CircleShape m_bullet_shape;
	sf::Vector2f m_bullet_position;
	float m_bullet_speed = 1000.0f;
	bool m_made_hit = false;
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

	void drawBullet(std::unique_ptr<sf::RenderWindow>&) const;
	void update(const sf::Time&);
};
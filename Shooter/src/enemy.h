#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Vector2f m_enemy_position;
	sf::Sprite m_enemy_sprite;
	float m_enemy_speed;
	bool m_enemy_hit = false;
public:
	Enemy() = delete;
	Enemy(int startX, int startY, const sf::Sprite&);
	Enemy(const Enemy&) = default;
	Enemy(Enemy&&) = default;
	Enemy& operator=(const Enemy&) = delete;
	Enemy& operator=(Enemy&&) = delete;
	~Enemy() = default;

	sf::FloatRect getPosition();
	int getX() const;
	void getHit();
	bool ifHitted() const;

	void draw(std::unique_ptr<sf::RenderWindow>&) const;
	void update(const sf::Time&);
};
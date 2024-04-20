#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum class GameState { ON, OFF, LOSE };

class Game
{
private:
	sf::Clock clock;
	sf::Time dt;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	sf::Music gameMusic;
	GameState gameState;

public:
	Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
	~Game() = default;

	void setMusic(const std::string&);
	void setBackground(const std::string&);
	GameState getState() const;
	void setState(GameState);

	void draw(sf::RenderWindow&);
};


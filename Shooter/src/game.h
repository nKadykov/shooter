#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

enum class GameState { ON, OFF, LOSE };

class Game
{
private:
	sf::Clock m_clock;
	sf::Time m_dt;
	sf::Texture m_background_texture;
	sf::Sprite m_background_sprite;
	sf::Music m_game_music;
	GameState m_game_state;
	int m_score;
	sf::Font m_font;
	sf::Text m_text_score;
public:
	Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
	//~Game() = default;

	void setMusic(const std::string&);
	void setBackground(const std::string&);
	GameState getState() const;
	void setState(GameState);

	void Start(std::unique_ptr<sf::RenderWindow>&);
};


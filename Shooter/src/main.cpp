#include <SFML/Graphics.hpp>
#include "game.h"
#include "menu.h"
#include "gameoverwindow.h"
#include <iostream>

enum class State { GAME, MENU, GAME_OVER };

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), L"Shooter", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    GameOverWindow game_over_window;
    game_over_window.setPosition(300, 200);

    Game *p_game = new Game();
    p_game->setMusic("music/back1.mp3");
    p_game->setBackground("images/back1.jpg");

    Menu menu;
    sf::Texture button_texture_1;
    sf::Texture button_texture_2;
    if (!button_texture_1.loadFromFile("images/button2.png")) {
        exit(1);
    }
    if (!button_texture_2.loadFromFile("images/button3.png")) {
        exit(1);
    }
    menu.addButton(500, 200, button_texture_1);
    menu.addButton(500, 400, button_texture_2);

    State state = State::MENU;
    ButtonState button_state = ButtonState::NONE;
    GameState game_state = GameState::ON;
    GameOverState game_over_state = GameOverState::OFF;

    while (window.isOpen()) {
        window.clear();

        button_state = menu.getButtonState();
        
        if (p_game) {
            game_state = p_game->getState();
        }
        game_over_state = game_over_window.getState();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (game_state == GameState::OFF || game_over_state == GameOverState::MENU) {
            if (p_game) {
                delete p_game;
                p_game = nullptr;
            }
            state = State::MENU;
            game_over_window.setState(GameOverState::ON);
        }
        if (game_state == GameState::LOSE) {
            if (p_game) {
                delete p_game;
                p_game = nullptr;
            }
            state = State::GAME_OVER;
            game_state = GameState::ON;
        }
        if (game_over_state == GameOverState::OFF || button_state == ButtonState::START_GAME) {
            p_game = new Game();
            p_game->setMusic("images/back1.mp3");
            p_game->setBackground("images/back1.jpg");
            state = State::GAME;
            game_over_window.setState(GameOverState::ON);
            menu.setButtonState(ButtonState::NONE);
        }
        if (button_state == ButtonState::CLOSE) {
            window.close();
        }

        switch (state) {
        case State::MENU:
            menu.draw(window);
            break;
        case State::GAME:
            p_game->draw(window);
            break;
        case State::GAME_OVER:
            game_over_window.draw(window);
            break;
        }
        window.display();
    }
    if (p_game) {
        delete p_game;
        p_game = nullptr;
    }
    return 0;
}
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

    Game *pGame = new Game();
    pGame->setMusic("resources/back1.mp3");
    pGame->setBackground("resources/back1.jpg");

    Menu menu;
    menu.addButton(500, 200, "resources/button2.png");
    menu.addButton(500, 400, "resources/button3.png");

    State state = State::MENU;
    ButtonState button_state = ButtonState::NONE;
    GameState game_state = GameState::ON;
    GameOverState game_over_state = GameOverState::OFF;

    while (window.isOpen()) {
        window.clear();

        button_state = menu.getButtonState();
        
        if (pGame) {
            game_state = pGame->getState();
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
            if (pGame) {
                delete pGame;
                pGame = nullptr;
            }
            state = State::MENU;
            game_over_window.setState(GameOverState::ON);
        }
        if (game_state == GameState::LOSE) {
            if (pGame) {
                delete pGame;
                pGame = nullptr;
            }
            state = State::GAME_OVER;
            game_state = GameState::ON;
        }
        if (game_over_state == GameOverState::OFF || button_state == ButtonState::START_GAME) {
            pGame = new Game();
            pGame->setMusic("resources/back1.mp3");
            pGame->setBackground("resources/back1.jpg");
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
            pGame->draw(window);
            break;
        case State::GAME_OVER:
            game_over_window.draw(window);
            break;
        }
        window.display();
    }
    if (pGame) {
        delete pGame;
        pGame = nullptr;
    }
    return 0;
}
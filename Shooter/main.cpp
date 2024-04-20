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

    GameOverWindow gameOverWindow;
    gameOverWindow.setPosition(300, 200);

    Game game;
    game.setMusic("resources/back1.mp3");
    game.setBackground("resources/back1.jpg");

    Menu menu;
    menu.addButton(500, 200, "resources/button2.png");
    menu.addButton(500, 400, "resources/button3.png");

    State state = State::MENU;
    ButtonState buttonState = ButtonState::NONE;
    GameState gameState = GameState::ON;
    GameOverState gameOverState = GameOverState::OFF;

    while (window.isOpen()) {
        window.clear();

        buttonState = menu.getButtonState();
        gameState = game.getState();
        gameOverState = gameOverWindow.getState();
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (gameState == GameState::OFF) {
            state = State::MENU;
            game.setState(GameState::ON);
        }
        else if (gameState == GameState::LOSE) {
            state = State::GAME_OVER;
            game.setState(GameState::ON);
        }
        else if (gameOverState == GameOverState::OFF || buttonState == ButtonState::START_GAME) {
            state = State::GAME;
            gameOverWindow.setState(GameOverState::ON);
            menu.setButtonState(ButtonState::NONE);
        }
        else if (gameOverState == GameOverState::MENU) {
            state = State::MENU;
            gameOverWindow.setState(GameOverState::ON);
        }
        if (buttonState == ButtonState::CLOSE) {
            window.close();
        }

        switch (state) {
        case State::MENU:
            menu.draw(window);
            break;
        case State::GAME:
            game.draw(window);
            break;
        case State::GAME_OVER:
            gameOverWindow.draw(window);
            break;
        }
        window.display();
    }
    return 0;
}
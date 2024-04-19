#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "GameOverWindow.h"
#include <iostream>

enum class State { gamestate, menustate, gameoverstate };

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

    State state = State::menustate;
    ButtonState buttonState = ButtonState::none;
    GameState gameState = GameState::on;
    GameOverState gameOverState = GameOverState::off;

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

        if (gameState == GameState::off) {
            state = State::menustate;
            game.setState(GameState::on);
        }
        else if (gameState == GameState::lose) {
            state = State::gameoverstate;
            game.setState(GameState::on);
        }
        else if (gameOverState == GameOverState::off || buttonState == ButtonState::button1) {
            state = State::gamestate;
            gameOverWindow.setState(GameOverState::on);
            menu.setButtonState(ButtonState::none);
        }
        else if (gameOverState == GameOverState::menu) {
            state = State::menustate;
            gameOverWindow.setState(GameOverState::on);
        }
        if (buttonState == ButtonState::button2) {
            window.close();
        }

        switch (state) {
        case State::menustate:
            menu.draw(window);
            break;
        case State::gamestate:
            game.draw(window);
            break;
        case State::gameoverstate:
            gameOverWindow.draw(window);
            break;
        }
        window.display();
    }
    return 0;
}
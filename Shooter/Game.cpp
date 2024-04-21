#include "game.h"
#include <iostream>
#include <list>
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "healthbar.h"

Game::Game() {
    game_state = GameState::ON;
    if (!game_music.openFromFile("resources/music.mp3")) {
        exit(1);
    }
    if (!background_texture.loadFromFile("resources/background.jpg")) {
        exit(1);
    }
}

void Game::setBackground(const std::string& filename) {
    if (!background_texture.loadFromFile(filename)) {
        background_texture.loadFromFile("resources/background.jpg");
    }
}

void Game::setMusic(const std::string& filename) {
    if (!game_music.openFromFile(filename)) {
        game_music.openFromFile("resources/music.mp3");
    }
}

GameState Game::getState() const {
    return game_state;
}

void Game::setState(GameState state) {
    game_state = state;
}

void Game::draw(sf::RenderWindow& window) {

    game_state = GameState::ON;

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("resources/enemy.png")) {
        exit(1);
    }
    sf::Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);

    sf::Texture healthPointTexture;
    if (!healthPointTexture.loadFromFile("resources/heart.png")) {
        exit(1);
    }
    sf::Sprite healthPointSprite;
    healthPointSprite.setTexture(healthPointTexture);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("resources/player1.png")) {
        exit(1);
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    game_music.play();
    background_sprite.setTexture(background_texture);
    Player player(10, 720 / 2, playerSprite);
    HealthBar healthBar(20, 20, healthPointSprite);
    healthBar.setHealth(player.getHealth());
    std::list<Bullet> bulletList;
    std::list<Enemy> enemyList;

    bool isFiring = false;

    float enemyTime = 0;
    float bulletTime = 0;
    float coutTime = 0;

    srand(time(NULL));

    while (window.isOpen() && game_state == GameState::ON)
    {
        window.draw(background_sprite);
        dt = clock.getElapsedTime();
        clock.restart();
        float t = dt.asSeconds();
        enemyTime += t;
        bulletTime += t;
        coutTime += t;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            game_state = GameState::OFF;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.moveDown();
        }
        else {
            player.stopDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            player.moveUp();
        }
        else {
            player.stopUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (bulletTime > 0.1) {
                isFiring = true;
            }
            bulletTime = 0;
        }

        if (isFiring == true) {
            Bullet newBullet(player.getPosition().left + 50, player.getPosition().top + 35);
            bulletList.push_back(newBullet);
            isFiring = false;
        }

        int enemyY = rand() % 600;

        if (enemyTime > 1) {
            Enemy newEnemy(1280 - 15, 50 + enemyY, enemySprite);
            enemyList.push_back(newEnemy);
            enemyTime = 0;
        }

        for (auto itBullet = bulletList.begin(); itBullet != bulletList.end(); itBullet++) {
            for (auto itEnemy = enemyList.begin(); itEnemy != enemyList.end(); itEnemy++) {
                if (itBullet->getPosition().intersects(itEnemy->getPosition())) {
                    itBullet->makeHit();
                    itEnemy->getHit();
                    continue;
                }
            }
        }

        auto itEnemy = enemyList.begin();
        while (itEnemy != enemyList.end()) {
            if (itEnemy->getX() < 0) {
                player.decreaseHealth();
                healthBar.decreaseHealth();
            }
            if (itEnemy->getX() < 0 || itEnemy->ifHitted()) {
                itEnemy = enemyList.erase(itEnemy);
                continue;
            }
            itEnemy++;
        }

        auto itBullet = bulletList.begin();
        while (itBullet != bulletList.end()) {
            if (itBullet->getX() > 1280 || itBullet->ifMadeHit()) {
                itBullet = bulletList.erase(itBullet);
                continue;
            }
            itBullet++;
        }

        for (auto it = enemyList.begin(); it != enemyList.end(); it++) {
            it->draw(window);
            it->update(dt);
        }

        for (auto it = bulletList.begin(); it != bulletList.end(); it++) {
            it->drawBullet(window);
            it->update(dt);
        }

        if (!player.ifAlive()) {
            game_state = GameState::LOSE;
        }

        player.update(dt);
        healthBar.draw(window);
        player.draw(window);
        window.display();
    }
    bulletList.clear();
    enemyList.clear();
}
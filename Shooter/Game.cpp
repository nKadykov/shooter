#include "Game.h"
#include <iostream>
#include <list>
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "HealthBar.h"

Game::Game() {
    if (!gameMusic.openFromFile("resources/music.mp3")) {
        exit(1);
    }
    if (!backgroundTexture.loadFromFile("resources/background.jpg")) {
        exit(1);
    }
}

void Game::setBackground(const std::string& filename) {
    if (!backgroundTexture.loadFromFile(filename)) {
        backgroundTexture.loadFromFile("resources/background.jpg");
    }
}

void Game::setMusic(const std::string& filename) {
    if (!gameMusic.openFromFile(filename)) {
        gameMusic.openFromFile("resources/music.mp3");
    }
}

GameState Game::getState() const {
    return gameState;
}

void Game::setState(GameState state) {
    gameState = state;
}

void Game::draw(sf::RenderWindow& window) {

    gameState = GameState::on;

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("resources/enemy.png");
    sf::Sprite enemySprite;
    enemySprite.setTexture(enemyTexture);

    sf::Texture healthPointTexture;
    healthPointTexture.loadFromFile("resources/heart.png");
    sf::Sprite healthPointSprite;
    healthPointSprite.setTexture(healthPointTexture);

    gameMusic.play();
    backgroundSprite.setTexture(backgroundTexture);
    Player player(10, 720 / 2);
    HealthBar healthBar(20, 20, healthPointSprite);
    healthBar.setHealth(player.getHealth());
    std::list<Bullet> bulletList;
    std::list<Enemy> enemyList;

    bool isFiring = false;

    float enemyTime = 0;
    float bulletTime = 0;
    float coutTime = 0;

    srand(time(NULL));

    while (window.isOpen() && (gameState == GameState::on))
    {
        window.draw(backgroundSprite);
        dt = clock.getElapsedTime();
        clock.restart();
        float t = dt.asSeconds();
        enemyTime += t;
        bulletTime += t;
        coutTime += t;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            gameState = GameState::off;
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
            gameState = GameState::lose;
        }

        player.update(dt);
        healthBar.draw(window);
        player.drawPlayer(window);
        window.display();
    }
    bulletList.clear();
    enemyList.clear();
}
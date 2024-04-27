#include "game.h"
#include <iostream>
#include <list>
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "healthbar.h"

Game::Game() {
    m_game_state = GameState::ON;
    if (!m_game_music.openFromFile("resources/music.mp3")) {
        exit(1);
    }
    if (!m_background_texture.loadFromFile("resources/background.jpg")) {
        exit(1);
    }
}

void Game::setBackground(const std::string& filename) {
    if (!m_background_texture.loadFromFile(filename)) {
        m_background_texture.loadFromFile("resources/background.jpg");
    }
}

void Game::setMusic(const std::string& filename) {
    if (!m_game_music.openFromFile(filename)) {
        m_game_music.openFromFile("resources/music.mp3");
    }
}

GameState Game::getState() const {
    return m_game_state;
}

void Game::setState(GameState state) {
    m_game_state = state;
}

void Game::draw(sf::RenderWindow& window) {

    m_game_state = GameState::ON;

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
    sf::Sprite health_point_sprite;
    health_point_sprite.setTexture(healthPointTexture);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("resources/player1.png")) {
        exit(1);
    }
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    m_game_music.play();
    m_background_sprite.setTexture(m_background_texture);
    Player player(10, 720 / 2, playerSprite);
    HealthBar m_healthBar(20, 20, health_point_sprite);
    m_healthBar.setHealth(player.getHealth());
    std::list<Bullet> bulletList;
    std::list<Enemy> enemyList;

    bool isFiring = false;

    float enemyTime = 0;
    float bulletTime = 0;
    float coutTime = 0;

    srand(time(nullptr));

    while (window.isOpen() && m_game_state == GameState::ON)
    {
        window.draw(m_background_sprite);
        m_dt = m_clock.getElapsedTime();
        m_clock.restart();
        float t = m_dt.asSeconds();
        enemyTime += t;
        bulletTime += t;
        coutTime += t;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            m_game_state = GameState::OFF;
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
                m_healthBar.decreaseHealth();
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
            it->update(m_dt);
        }

        for (auto it = bulletList.begin(); it != bulletList.end(); it++) {
            it->drawBullet(window);
            it->update(m_dt);
        }

        if (!player.ifAlive()) {
            m_game_state = GameState::LOSE;
        }

        player.update(m_dt);
        m_healthBar.draw(window);
        player.draw(window);
        window.display();
    }
    bulletList.clear();
    enemyList.clear();
}
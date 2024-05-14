#include "game.h"
#include <iostream>
#include <list>
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "healthbar.h"

Game::Game() {
    m_game_state = GameState::ON;
    if (!m_game_music.openFromFile("music/music.mp3")) {
        exit(1);
    }
    if (!m_background_texture.loadFromFile("images/background.jpg")) {
        exit(1);
    }
}

void Game::setBackground(const std::string& filename) {
    if (!m_background_texture.loadFromFile(filename)) {
        m_background_texture.loadFromFile("images/background.jpg");
    }
}

void Game::setMusic(const std::string& filename) {
    if (!m_game_music.openFromFile(filename)) {
        m_game_music.openFromFile("music/music.mp3");
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

    sf::Texture enemy_texture;
    if (!enemy_texture.loadFromFile("images/enemy.png")) {
        exit(1);
    }
    sf::Sprite enemy_sprite;
    enemy_sprite.setTexture(enemy_texture);

    sf::Texture health_point_texture;
    if (!health_point_texture.loadFromFile("images/heart.png")) {
        exit(1);
    }
    sf::Sprite health_point_sprite;
    health_point_sprite.setTexture(health_point_texture);

    sf::Texture player_texture;
    if (!player_texture.loadFromFile("images/player1.png")) {
        exit(1);
    }
    sf::Sprite player_sprite;
    player_sprite.setTexture(player_texture);

    m_game_music.play();
    m_background_sprite.setTexture(m_background_texture);
    Player player(10, 720 / 2, player_sprite);
    HealthBar m_healthBar(20, 20, health_point_sprite);
    m_healthBar.setHealth(player.getHealth());
    std::list<Bullet> bullet_list;
    std::list<Enemy> enemy_list;

    bool is_firing = false;

    float enemy_time = 0;
    float bullet_time = 0;

    srand(time(nullptr));

    while (window.isOpen() && m_game_state == GameState::ON)
    {
        window.draw(m_background_sprite);
        m_dt = m_clock.getElapsedTime();
        m_clock.restart();
        float t = m_dt.asSeconds();
        enemy_time += t;
        bullet_time += t;

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
            if (bullet_time > 0.1) {
                is_firing = true;
            }
            bullet_time = 0;
        }

        if (is_firing == true) {
            Bullet new_bullet(player.getPosition().left + 50, player.getPosition().top + 35);
            bullet_list.push_back(new_bullet);
            is_firing = false;
        }

        int enemy_y = rand() % 600;

        if (enemy_time > 1) {
            Enemy new_enemy(1280 - 15, 50 + enemy_y, enemy_sprite);
            enemy_list.push_back(new_enemy);
            enemy_time = 0;
        }

        for (auto it_bullet = bullet_list.begin(); it_bullet != bullet_list.end(); it_bullet++) {
            for (auto it_enemy = enemy_list.begin(); it_enemy != enemy_list.end(); it_enemy++) {
                if (it_bullet->getPosition().intersects(it_enemy->getPosition())) {
                    it_bullet->makeHit();
                    it_enemy->getHit();
                    continue;
                }
            }
        }

        auto it_enemy = enemy_list.begin();
        while (it_enemy != enemy_list.end()) {
            if (it_enemy->getX() < 0) {
                player.decreaseHealth();
                m_healthBar.decreaseHealth();
            }
            if (it_enemy->getX() < 0 || it_enemy->ifHitted()) {
                it_enemy = enemy_list.erase(it_enemy);
                continue;
            }
            it_enemy++;
        }

        auto it_bullet = bullet_list.begin();
        while (it_bullet != bullet_list.end()) {
            if (it_bullet->getX() > 1280 || it_bullet->ifMadeHit()) {
                it_bullet = bullet_list.erase(it_bullet);
                continue;
            }
            it_bullet++;
        }

        for (auto it = enemy_list.begin(); it != enemy_list.end(); it++) {
            it->draw(window);
            it->update(m_dt);
        }

        for (auto it = bullet_list.begin(); it != bullet_list.end(); it++) {
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
    bullet_list.clear();
    enemy_list.clear();
}
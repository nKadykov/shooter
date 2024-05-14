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

    m_score = 0;
    if (!m_font.loadFromFile("fonts/ImpactRegular.ttf")) {
        exit(1);
    }
    m_text_score.setFont(m_font);
    m_text_score.setPosition(900, 10);
    m_text_score.setOutlineColor(sf::Color::Black);
    m_text_score.setOutlineThickness(4);
    m_text_score.setCharacterSize(40);
    m_text_score.setString("Score: " + std::to_string(m_score));
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

void Game::Start(std::unique_ptr<sf::RenderWindow>& window) {

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
    std::unique_ptr<Player> p_player = std::make_unique<Player>(10, 720 / 2, player_sprite);
    std::unique_ptr<HealthBar> p_health_bar = std::make_unique<HealthBar>(20, 20, health_point_sprite);
    p_health_bar->setHealth(p_player->getHealth());
    std::list<std::unique_ptr<Bullet>> bullet_list;
    std::list<std::unique_ptr<Enemy>> enemy_list;

    bool is_firing = false;

    float enemy_time = 0;
    float bullet_time = 0;

    srand(time(nullptr));

    while (window->isOpen() && m_game_state == GameState::ON)
    {
        window->draw(m_background_sprite);
        m_dt = m_clock.getElapsedTime();
        m_clock.restart();
        float t = m_dt.asSeconds();
        enemy_time += t;
        bullet_time += t;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            m_game_state = GameState::OFF;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window->close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            p_player->moveDown();
        }
        else {
            p_player->stopDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            p_player->moveUp();
        }
        else {
            p_player->stopUp();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            if (bullet_time > 0.1) {
                is_firing = true;
            }
            bullet_time = 0;
        }

        if (is_firing == true) {
            std::unique_ptr<Bullet> p_new_bullet = std::make_unique<Bullet>(p_player->getPosition().left + 50, p_player->getPosition().top + 35);
            bullet_list.push_back(std::move(p_new_bullet));
            is_firing = false;
        }

        int enemy_y = rand() % 580;

        if (enemy_time > 1) {
            std::unique_ptr<Enemy> p_new_enemy = std::make_unique<Enemy>(1280, 50 + enemy_y, enemy_sprite);
            enemy_list.push_back(std::move(p_new_enemy));
            enemy_time = 0;
        }

        for (auto it_bullet = bullet_list.begin(); it_bullet != bullet_list.end(); it_bullet++) {
            for (auto it_enemy = enemy_list.begin(); it_enemy != enemy_list.end(); it_enemy++) {
                if ((*it_bullet)->getPosition().intersects((*it_enemy)->getPosition())) {
                    m_score++;
                    m_text_score.setString("Score: " + std::to_string(m_score));
                    (*it_bullet)->makeHit();
                    (*it_enemy)->getHit();
                    continue;
                }
            }
        }

        auto it_enemy = enemy_list.begin();
        while (it_enemy != enemy_list.end()) {
            if ((*it_enemy)->getX() < 0) {
                p_player->decreaseHealth();
                p_health_bar->decreaseHealth();
            }
            if ((*it_enemy)->getX() < 0 || (*it_enemy)->ifHitted()) {
                it_enemy = enemy_list.erase(it_enemy);
                continue;
            }
            it_enemy++;
        }

        auto it_bullet = bullet_list.begin();
        while (it_bullet != bullet_list.end()) {
            if ((*it_bullet)->getX() > 1280 || (*it_bullet)->ifMadeHit()) {
                it_bullet = bullet_list.erase(it_bullet);
                continue;
            }
            it_bullet++;
        }

        for (auto it = enemy_list.begin(); it != enemy_list.end(); it++) {
            (*it)->draw(window);
            (*it)->update(m_dt);
        }

        for (auto it = bullet_list.begin(); it != bullet_list.end(); it++) {
            (*it)->drawBullet(window);
            (*it)->update(m_dt);
        }

        if (!p_player->ifAlive()) {
            m_game_state = GameState::LOSE;
        }

        p_player->update(m_dt);
        p_health_bar->draw(window);
        p_player->draw(window);
        window->draw(m_text_score);
        window->display();
    }
    bullet_list.clear();
    enemy_list.clear();
}
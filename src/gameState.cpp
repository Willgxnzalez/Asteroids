#include "gameState.hpp"
#include "resourceManager.hpp"
#include "stateManager.hpp"
#include "config.hpp"
#include <iostream>
#include <cmath>

GameState::GameState(StateManager& stateManager) 
    : State(stateManager), ship(Config::SCREEN_WIDTH / 2, Config::SCREEN_HEIGHT /2), astsPerRound(3), score(0)
{
    updateScoreStr();
    scoreText.setFont(ResourceManager::getFont("rsrc/asteroids_font.ttf"));
    scoreText.setCharacterSize(Config::FONT_SIZE);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(Config::HUD_HEIGHT, Config::HUD_HEIGHT);

    updateRoundStr();
    roundText.setFont(ResourceManager::getFont("rsrc/asteroids_font.ttf"));
    roundText.setCharacterSize(Config::FONT_SIZE);
    roundText.setFillColor(sf::Color::White);
    roundText.setPosition((Config::SCREEN_WIDTH - roundText.getLocalBounds().width) / 2.0f, Config::HUD_HEIGHT);
    
    spawnAsteroids(astsPerRound);
}

void GameState::handleEvent(const sf::Event &event) 
{
    switch (event.type) {
        case sf::Event::KeyPressed: keysPressed[event.key.code] = true; break;

        case sf::Event::KeyReleased: keysPressed[event.key.code] = false; break;
        /*
        case sf::Event::MouseButtonPressed: 
            if (event.mouseButton.button == sf::Mouse::Left) leftMousePressed = true;
            else if (event.mouseButton.button == sf::Mouse::Right) rightMousePressed = true;
            break;

        case sf::Event::MouseButtonReleased: 
            if (event.mouseButton.button == sf::Mouse::Left) leftMousePressed = false;
            else if (event.mouseButton.button == sf::Mouse::Right) rightMousePressed = false;
            break;
        */
        default: return;
    }
}

void GameState::update(float deltaTime) 
{
    if (keysPressed[sf::Keyboard::W]) ship.accelerate(deltaTime); else ship.idle();
    if (keysPressed[sf::Keyboard::A]) ship.rotate(-Spaceship::ROTATION_SPEED * deltaTime);
    if (keysPressed[sf::Keyboard::D]) ship.rotate(Spaceship::ROTATION_SPEED * deltaTime);
    if (keysPressed[sf::Keyboard::Space] || leftMousePressed  || keysPressed[sf::Keyboard::Up]) ship.shoot();

    ship.update(deltaTime);

    for (Bullet &bullet: ship.getBullets()) bullet.update(deltaTime);
    for (Asteroid &asteroid: asteroids) asteroid.update(deltaTime);
    
    std::vector<Bullet> & bullets = ship.getBullets();
    bullets.erase( // erase-remove  idiom
        std::remove_if(bullets.begin(), bullets.end(), [this](const Bullet &bullet) {
            bool offScreen = bullet.isOffScreen();
            if (offScreen) {
                score = std::max(score - 10, 0);
                ship.logMissedBullet();
                updateScoreStr();
            } 
            return offScreen;
        }),
        bullets.end()
    );

    checkCollisions();

    if (ship.getLives() <= 0) {
        stateManager.setState(StateType::Gameover);
        std::cout << "Accruacy: " << ship.getAccuracy() << std::endl;
    }
    if (asteroids.empty()) {
        spawnAsteroids(++astsPerRound);
        updateRoundStr();
    }
}

void GameState::render(sf::RenderWindow &window) 
{
    window.clear(sf::Color::Black);
    
    for (Bullet &bullet: ship.getBullets()) bullet.render(window);
    for (Asteroid &asteroid : asteroids) asteroid.render(window);
    
    ship.render(window);

    window.draw(scoreText);
    window.draw(roundText);

    window.display();
}

void GameState::checkCollisions() {
    std::vector<size_t> bulletsToRemove;
    std::vector<size_t> asteroidsToRemove;

    std::vector<Bullet> & bullets = ship.getBullets();
    for (size_t i = 0; i < bullets.size(); ++i) {
        for (size_t j = 0; j < asteroids.size(); ++j) {
            if (getDistanceBetween(bullets[i].getPosition(), asteroids[j].getPosition()) <= asteroids[j].getRadius()) {
                bulletsToRemove.push_back(i);
                asteroidsToRemove.push_back(j);
                splitAsteroid(asteroids[j]);
                break;  // Move to the next bullet after detecting a collision
            }
        }
    }

    // Spaceship - Asteroid collisions
    for (size_t j = 0; j < asteroids.size(); ++j) {
        if (getDistanceBetween(ship.getPosition(), asteroids[j].getPosition()) <= asteroids[j].getRadius() + ship.getWidth() / 2) {
            asteroidsToRemove.push_back(j);
            ship.explode();
            break;
        }
    }

    removeEntities(bullets, bulletsToRemove);
    removeEntities(asteroids, asteroidsToRemove);
}

float GameState::getDistanceBetween(sf::Vector2f pos1, sf::Vector2f pos2) const {
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    return static_cast<float>(std::sqrt(dx * dx + dy * dy));
}

void GameState::spawnAsteroids(int count) {
    for (int i = 0; i < count; ++i) {
        Asteroid asteroid(3, Asteroid::getRandomPosition(ship.getPosition()), Asteroid::getRandomDirection());  // Large asteroid
        asteroids.push_back(asteroid);
    }
}

void GameState::splitAsteroid(Asteroid &asteroid)
{
    int newSize = asteroid.getSize() - 1;
    switch (newSize) {
        case 2: score += Asteroid::LARGE_ASTEROID_POINT_VALUE; break;
        case 1: score += Asteroid::MEDIUM_ASTEROID_POINT_VALUE; break;
        case 0: score += Asteroid::SMALL_ASTEROID_POINT_VALUE; break;
    }
    updateScoreStr();
    
    if (newSize > 0) {
        for (int i = 0; i < 2; ++i) {
            asteroids.emplace_back(newSize, asteroid.getPosition(), Asteroid::getRandomDirection());
        }
    }
}

template <typename T>
void GameState::removeEntities(std::vector<T>& entityCollection, const std::vector<size_t>& indicesToRemove) {
    std::vector<size_t> sortedIndices(indicesToRemove);
    std::sort(sortedIndices.rbegin(), sortedIndices.rend());

    for (size_t index : sortedIndices) {
        entityCollection.erase(entityCollection.begin() + index);
    }
}

void GameState::updateScoreStr() {
    static size_t width = 6;
    std::string scoreStr = std::to_string(std::max(score, 0));
    if (scoreStr.length() < width) {
        scoreStr.insert(0, width - scoreStr.length(), '0');
    }
    scoreText.setString(scoreStr);
}

void GameState::updateRoundStr() {
    static size_t width = 2;
    std::string roundStr = std::to_string(astsPerRound - 2);
    if (roundStr.length() < width) {
        roundStr.insert(0, 1, '0');
    }
    roundText.setString(roundStr);
}

#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"
#include "state.hpp"
#include "spaceship.hpp"
#include <unordered_map>
#include <vector>
#include "asteroid.hpp"

class GameState : public State
{
    std::unordered_map<sf::Keyboard::Key, bool> keysPressed;
    bool leftMousePressed;
    bool rightMousePressed;
    std::vector<Asteroid> asteroids;

    Spaceship ship;

    int astsPerRound;
    int score;

    sf::Text scoreText;
    sf::Text roundText;

public:
    GameState(StateManager& stateManager);
    ~GameState() = default;

    void handleEvent(const sf::Event &event);
    void update(float deltaTime);
    void render(sf::RenderWindow &window);

private:
    float getDistanceBetween(sf::Vector2f pos1, sf::Vector2f pos2) const;
    void checkCollisions();
    void spawnAsteroids(int count);
    void splitAsteroid(Asteroid &asteroid);

    template <typename T>
    void removeEntities(std::vector<T>& entityCollection, const std::vector<size_t>& indicesToRemove);
    void updateScoreStr(); 
    void updateRoundStr();
}; 
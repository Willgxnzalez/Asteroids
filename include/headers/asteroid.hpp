#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"

class Asteroid
{
    static constexpr float LARGE_ASTEROID_SPEED = 1.0f;
    static constexpr float MEDIUM_ASTEROID_SPEED  = 1.5f;
    static constexpr float SMALL_ASTEROID_SPEED = 2.0f;

    sf::Sprite sprite;

    int size;
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;

public:
    Asteroid(int size, sf::Vector2f position, sf::Vector2f direction);
    ~Asteroid() = default;

    void update(float deltaTime);
    void render(sf::RenderWindow &window);

    int getSize() const;
    float getRadius() const;
    sf::Vector2f getPosition() const;
    static sf::Vector2f getRandomDirection();
    static sf::Vector2f getRandomPosition();
    static sf::Vector2f getRandomPosition(const sf::Vector2f& shipPosition);

    static constexpr int LARGE_ASTEROID_POINT_VALUE = 100;
    static constexpr int MEDIUM_ASTEROID_POINT_VALUE  = 150;
    static constexpr int SMALL_ASTEROID_POINT_VALUE = 200;

private:
    static float getSpeedForSize(int size);
    void wrapScreen();

};
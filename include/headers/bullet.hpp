#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"

class Bullet
{
    sf::CircleShape texture;
    sf::Vector2f position;
    sf::Vector2f direction;

public:
    Bullet(sf::Vector2f startPos, sf::Vector2f dir);
    ~Bullet() = default;
    
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    
    bool isOffScreen() const;
    sf::Vector2f getPosition() const;

    static constexpr float BULLET_RADIUS = 1.5f;
    static constexpr float BULLET_SPEED = 7.0f;
};
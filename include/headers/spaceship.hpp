#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"
#include "bullet.hpp"
#include <vector>


class Spaceship 
{
    static constexpr float PI = 3.14159265f;
    static constexpr float SHIP_SIZE = 20.0f;
    static constexpr float ACCELERATION = 0.1f;
    static constexpr float FRICTION = 0.9999f;
    static constexpr float SHOOT_COOLDOWN = 0.08f; // Time between shots in seconds
    static constexpr int MAX_BULLETS_ON_SCREEN = 8;

  
    sf::Vector2f position;
    sf::Vector2f direction;
    sf::Vector2f velocity;

    float shipWidth;
    float shipHeight;
    float lives;

    sf::Sprite sprites[2]; // 0: idle, 1: thrust
    int animationIndex;
    sf::Sprite lifeSprite;
    sf::Clock shootClock;  // Clock to manage shooting intervals

    std::vector<Bullet> bullets;
    int bulletsFired;
    int bulletsMissed;

public:
    Spaceship(float x, float y);
    ~Spaceship() = default;

    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    
    void rotate(float deltaAngle);
    void accelerate(float deltaTime);
    void shoot();
    void explode();
    void idle();
    void logMissedBullet();

    sf::Vector2f getPosition() const;
    float getWidth() const;
    std::vector<Bullet>& getBullets();
    float getLives() const;
    float getAccuracy() const;
    
    static constexpr float ROTATION_SPEED = 3.0f;


private:
    void wrapScreen();
};
#include "asteroid.hpp"
#include "resourceManager.hpp"
#include "config.hpp"
#include <cmath>
#include <iostream>

Asteroid::Asteroid(int size, sf::Vector2f position, sf::Vector2f direction)
    : size(size), radius(static_cast<float>(size) * Config::SCREEN_WIDTH / 100.0f), position(position), velocity(direction * getSpeedForSize(size))
{

    sprite.setTexture(ResourceManager::getTexture(
        (size == 1) ? "rsrc/sprites/asteroid_small.png" : 
        (size == 2) ? "rsrc/sprites/asteroid_med.png" : 
        "rsrc/sprites/asteroid_large.png"
    ));

    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    sprite.setPosition(position);

    float textureWidth = static_cast<float>(sprite.getTexture()->getSize().x);
    float textureHeight = static_cast<float>(sprite.getTexture()->getSize().y);
    float scaleX = (radius * 2.0f) / textureWidth;
    float scaleY = (radius * 2.0f) / textureHeight;
    sprite.setScale(scaleX, scaleY);
}

void Asteroid::update(float deltaTime)
{
    position += velocity * deltaTime;

    wrapScreen();

    sprite.setPosition(position);
}

void Asteroid::render(sf::RenderWindow &window)
{
    window.draw(sprite);
}

int Asteroid::getSize() const
{
    return size;
}

float Asteroid::getRadius() const
{
    return radius;
}

sf::Vector2f Asteroid::getPosition() const 
{
    return position;
}

sf::Vector2f Asteroid::getRandomDirection() 
{
    float angle = static_cast<float>(std::rand() % 360) * 3.14159265359f / 180.0f; // in radians
    return sf::Vector2f(std::cos(angle), std::sin(angle));
}

sf::Vector2f Asteroid::getRandomPosition(const sf::Vector2f& shipPosition) 
{
    float x, y, dx, dy;
    static const float minDistance = 75.0f; // Minimum distance from the ship

    do {
        x = static_cast<float>(std::rand()) / RAND_MAX * Config::SCREEN_WIDTH;
        y = static_cast<float>(std::rand()) / RAND_MAX * Config::SCREEN_HEIGHT;

        dx = x - shipPosition.x;
        dy = y - shipPosition.y;
    } while (std::sqrt(dx * dx + dy * dy) <= minDistance);

    return sf::Vector2f(x, y);
}

sf::Vector2f Asteroid::getRandomPosition()
{
    float x = static_cast<float>(std::rand()) / RAND_MAX * Config::SCREEN_WIDTH;
    float y = static_cast<float>(std::rand()) / RAND_MAX * Config::SCREEN_HEIGHT;
    return sf::Vector2f(x, y);
}


float Asteroid::getSpeedForSize(int size) 
{
    switch (size) {
        case 3: return LARGE_ASTEROID_SPEED;
        case 2: return MEDIUM_ASTEROID_SPEED;
        case 1: return SMALL_ASTEROID_SPEED;
        default: return 0.0f;
    }
}

void Asteroid::wrapScreen()
{
    position.x = static_cast<float>(std::fmod(position.x + Config::SCREEN_WIDTH, Config::SCREEN_WIDTH));
    position.y = static_cast<float>(std::fmod(position.y + Config::SCREEN_HEIGHT, Config::SCREEN_HEIGHT));
}
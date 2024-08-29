#include "bullet.hpp"
#include "config.hpp"
#include <iostream>

Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f dir) 
    :position(startPos), direction(dir)
{
    texture.setRadius(BULLET_RADIUS);
    texture.setFillColor(sf::Color::White);
    texture.setOrigin(BULLET_RADIUS, BULLET_RADIUS);
}

void Bullet::update(float deltaTime)
{
    position += direction * BULLET_SPEED * deltaTime;
    texture.setPosition(position);
}

void Bullet::render(sf::RenderWindow &window)
{
    window.draw(texture);
}

bool Bullet::isOffScreen() const
{
    return (position.x < 0 || position.x > Config::SCREEN_WIDTH || position.y < 0 || position.y > Config::SCREEN_HEIGHT);
}

sf::Vector2f Bullet::getPosition() const
{
    return position;
}
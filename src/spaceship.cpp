#include "spaceship.hpp"
#include "resourceManager.hpp"
#include <cmath>
#include "config.hpp"
#include <iostream>


Spaceship::Spaceship(float x, float y)
    : position(x, y), direction(0, -1), velocity(0, 0), 
      shipWidth(Config::SCREEN_WIDTH / 50.0f), shipHeight(Config::SCREEN_HEIGHT / 25.0f), lives(3),
      animationIndex(0), 
      bulletsFired(0), bulletsMissed(0)
{
    sprites[0].setTexture(ResourceManager::getTexture("rsrc/sprites/spaceship-idle.png"));
    sprites[1].setTexture(ResourceManager::getTexture("rsrc/sprites/spaceship-thrust.png"));

    float scaleX, scaleY;
    for (int i = 0; i < 2; ++i) {
        sf::FloatRect bounds = sprites[i].getLocalBounds();
        sprites[i].setOrigin(bounds.width / 2, bounds.height / 2); //center origin

        scaleX = shipWidth / static_cast<float>(bounds.width);
        scaleY = shipHeight/ static_cast<float>(bounds.height);
        sprites[i].setScale(scaleX, scaleY);

        sprites[i].setPosition(x, y);
    }


    lifeSprite.setTexture(ResourceManager::getTexture("rsrc/sprites/spaceship-idle.png"));
    lifeSprite.setScale(scaleX * 0.8f, scaleY * 0.8f);
}

void Spaceship::update(float deltaTime)
{
    position += velocity * deltaTime;
    velocity *= FRICTION; 

    wrapScreen();

    sprites[animationIndex].setPosition(position);
}

void Spaceship::render(sf::RenderWindow &window)
{
    static const float offset = 20.0f;
    static const float startX = Config::SCREEN_WIDTH - Config::HUD_HEIGHT;  
    static const float startY = Config::HUD_HEIGHT;
    
    for (float i = 1; i <= lives; ++i) {
        lifeSprite.setPosition(startX - i * (lifeSprite.getGlobalBounds().width + offset), startY);
        window.draw(lifeSprite);
    }

    window.draw(sprites[animationIndex]);
}

void Spaceship::rotate(float deltaAngle) 
{
    float radians = deltaAngle * PI / 180;
    float sinAngle = std::sin(radians);
    float cosAngle = std::cos(radians);

    // 2D vector rotation 
    float newX = direction.x * cosAngle - direction.y * sinAngle;
    float newY = direction.x * sinAngle + direction.y * cosAngle;
    direction = sf::Vector2f(newX, newY);
    direction = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y); // Normalize

    sprites[0].rotate(deltaAngle);
    sprites[1].rotate(deltaAngle);
}

void Spaceship::accelerate(float deltaTime)
{ 
    animationIndex = 1;
    velocity += direction * ACCELERATION * deltaTime;
}

void Spaceship::shoot()
{
    if (shootClock.getElapsedTime().asSeconds() >= SHOOT_COOLDOWN and bullets.size() <= MAX_BULLETS_ON_SCREEN) {
        ++bulletsFired;
        bullets.emplace_back(position + (direction * (shipHeight / 2)), direction); 
        shootClock.restart();
    }
}

void Spaceship::explode()
{
    --lives;
}

void Spaceship::idle()
{
    animationIndex = 0;
}

void Spaceship::logMissedBullet()
{
    ++bulletsMissed;
}

sf::Vector2f Spaceship::getPosition() const
{
    return position;
}

float Spaceship::getWidth() const
{
    return shipWidth;
}

std::vector<Bullet>& Spaceship::getBullets() 
{
    return bullets;
}

float Spaceship::getLives() const
{
    return lives;
}

float Spaceship::getAccuracy() const
{
    return (static_cast<float>(bulletsFired) - static_cast<float>(bulletsMissed)) / static_cast<float>(bulletsFired) * 100.0f;
}


void Spaceship::wrapScreen()
{
    position.x = static_cast<float>(std::fmod(position.x + Config::SCREEN_WIDTH, Config::SCREEN_WIDTH));
    position.y = static_cast<float>(std::fmod(position.y + Config::SCREEN_HEIGHT, Config::SCREEN_HEIGHT));
}
#pragma once
#include "state.hpp"
#include <SFML/Graphics.hpp>
#include "asteroid.hpp"
#include <vector>

class IntroState : public State 
{
public:
    IntroState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Text titleText;
    sf::Text startText;

    sf::Clock startBtnClock;
    float START_BTN_INTERVAL = 1.0f;
    bool showStartText;

    std::vector<Asteroid> asteroids;
    static constexpr int NUM_FAKE_ASTEROIDS = 15;
};
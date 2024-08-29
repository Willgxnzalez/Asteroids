#pragma once
#include "state.hpp"
#include <SFML/Graphics.hpp>

class GameOverState : public State 
{
public:
    GameOverState(StateManager& stateManager);
    void handleEvent(const sf::Event& event) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Text gameOverText;
};

#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"

class StateManager; // forward declaration avoids including state.hpp

enum class StateType 
{
    None,
    Intro,
    Game,
    Gameover
};

class State 
{
public:
    explicit State(StateManager& stateManager) : stateManager(stateManager) {}
    virtual void handleEvent(const sf::Event &event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow &window) = 0;
    virtual ~State() = default;

protected:
    StateManager& stateManager;
};
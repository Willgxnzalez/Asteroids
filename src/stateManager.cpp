#include "stateManager.hpp"
#include "introState.hpp"
#include "gameState.hpp"
#include "gameOverState.hpp"
#include <iostream>


StateManager::StateManager()
    : currentState(StateType::None), pendingState(StateType::None), stateChangePending(false)
{
    states[StateType::Intro] = std::make_unique<IntroState>(*this);
    states[StateType::Game] = std::make_unique<GameState>(*this);
    states[StateType::Gameover] = std::make_unique<GameOverState>(*this);
}

void StateManager::setState(StateType stateType) 
{
    if (stateExists(stateType)) {
        pendingState = stateType;
        stateChangePending = true;
    } else {
        std::cerr << "Error: State not found." << std::endl;
    }
}

void StateManager::handleEvent(const sf::Event &event) 
{
    if (stateExists(currentState)) {
        states[currentState]->handleEvent(event);
    }
}

void StateManager::update(float deltaTime) 
{
    if (stateExists(currentState)) {
        states[currentState]->update(deltaTime);
    }
}

void StateManager::render(sf::RenderWindow &window)
{
    if (stateExists(currentState)) {
        states[currentState]->render(window);
    }
}

bool StateManager::stateExists(StateType stateType) const
{
    return states.find(stateType) != states.end();
}

void StateManager::handleStateTransition() {
    if (stateChangePending) {
        currentState = pendingState;
        stateChangePending = false;
    }
}
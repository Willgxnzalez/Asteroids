#pragma once

#include <map>
#include <memory>
#include "state.hpp"


class StateManager 
{
    std::map<StateType, std::unique_ptr<State>> states; // holds states inside map
    StateType currentState;
    StateType pendingState;
    bool stateChangePending;
    
public:
    StateManager();
    ~StateManager() = default;
    void setState(StateType stateType);
    void handleEvent(const sf::Event &event);
    void update(float deltaTime);
    void render(sf::RenderWindow &window);
    void handleStateTransition();

private:
    bool stateExists(StateType stateType) const;
};

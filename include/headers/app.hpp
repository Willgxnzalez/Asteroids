#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"
#include "stateManager.hpp"


class App 
{
    sf::RenderWindow window;
    StateManager stateManager;

public:
    App();
    ~App() = default;
    void run();
};
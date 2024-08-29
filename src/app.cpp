#include <iostream>
#include <memory>
#include "app.hpp"
#include "state.hpp"
#include "config.hpp"


App::App() 
    : window(sf::VideoMode(static_cast<unsigned int>(Config::SCREEN_WIDTH), static_cast<unsigned int>(Config::SCREEN_HEIGHT)), Config::TITLE)
{
    if (!window.isOpen()) {
        std::cerr << "Failed to create window\n";
        exit(EXIT_FAILURE);
    } else {
        std::cout << "Window created successfully\n";
    }

    stateManager.setState(StateType::Intro);
}

void App::run() 
{
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {                          
                window.close();
            }
            stateManager.handleEvent(event);
        }
        stateManager.update(clock.restart().asSeconds() * 100.0f);
        stateManager.render(window);
        stateManager.handleStateTransition();
    }
}
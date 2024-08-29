#include "introState.hpp"
#include "resourceManager.hpp"
#include "stateManager.hpp"
#include "config.hpp"

IntroState::IntroState(StateManager& stateManager) 
    : State(stateManager), showStartText(true)
{
    titleText.setFont(ResourceManager::getFont("rsrc/asteroids_font.ttf"));
    titleText.setString(Config::TITLE);
    titleText.setCharacterSize(100);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(
        (Config::SCREEN_WIDTH - titleText.getLocalBounds().width) / 2.0f,
        Config::SCREEN_HEIGHT / 4.0f
    );

    startText.setFont(ResourceManager::getFont("rsrc/asteroids_font.ttf"));
    startText.setString("space-to-start");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(
        (Config::SCREEN_WIDTH - startText.getLocalBounds().width) / 2.0f,
        Config::SCREEN_HEIGHT * 3.0f / 4.0f
    );

    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned>(std::time(0)));

    for (int i = 0; i < NUM_FAKE_ASTEROIDS; ++i) {
        int randomSize = (std::rand() % 3) + 1;
        Asteroid asteroid(randomSize, Asteroid::getRandomPosition(), Asteroid::getRandomDirection());
        asteroids.push_back(asteroid);
    }

}

void IntroState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
            stateManager.setState(StateType::Game);
        }

    }
}

void IntroState::update(float deltaTime) {
    for (Asteroid &asteroid: asteroids) asteroid.update(deltaTime);

    if (startBtnClock.getElapsedTime().asSeconds() >= START_BTN_INTERVAL) {
        showStartText = !showStartText;
        startBtnClock.restart();
    }
}

void IntroState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    
    for (Asteroid &asteroid : asteroids) asteroid.render(window);

    window.draw(titleText);
    if (showStartText) 
        window.draw(startText);


    window.display();
}

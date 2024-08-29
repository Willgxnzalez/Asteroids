#include "gameOverState.hpp"
#include "resourceManager.hpp"
#include "config.hpp"

GameOverState::GameOverState(StateManager& stateManager) 
    : State(stateManager)
{
    gameOverText.setFont(ResourceManager::getFont("rsrc/asteroids_font.ttf"));
    gameOverText.setString("Game Over\nPress any key to exit");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(
        (Config::SCREEN_WIDTH - gameOverText.getLocalBounds().width) / 2.0f,
        (Config::SCREEN_HEIGHT - gameOverText.getLocalBounds().height) / 2.0f
    );
}

void GameOverState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        exit(0);
    }
}

void GameOverState::update(float /*deltaTime*/) {
}

void GameOverState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(gameOverText);
    window.display();
}

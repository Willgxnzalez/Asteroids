#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"

namespace Config {
    constexpr char TITLE[] = "Asteroids";

    static const float SCREEN_WIDTH = [] {
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        return static_cast<float>(desktopMode.width * 0.6);
    }();

    static const float SCREEN_HEIGHT = [] {
        sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
        return static_cast<float>(desktopMode.height * 0.7);
    }();

    static const float HUD_HEIGHT = SCREEN_HEIGHT / 24.0f;
    static const unsigned int FONT_SIZE = static_cast<unsigned int>(SCREEN_HEIGHT / 24);
    constexpr int FPS = 60;
}
#include "ResourceManager.hpp"
#include <iostream>

sf::Texture& ResourceManager::getTexture(const std::string& filename)
{
    auto& instance = getInstance();
    auto& textures = instance.textures;

    // Load texture if not already loaded
    if (textures.find(filename) == textures.end()) {
        if (!textures[filename].loadFromFile(filename)) {
            std::cerr << "Failed to load texture: " << filename << '\n';
        }
    }

    return textures[filename];
}

sf::Font& ResourceManager::getFont(const std::string& filename)
{
    auto& instance = getInstance();
    auto& fonts = instance.fonts;

    // Load font if not already loaded
    if (fonts.find(filename) == fonts.end()) {
        if (!fonts[filename].loadFromFile(filename)) {
            std::cerr << "Failed to load font: " << filename << '\n';
        }
    }

    return fonts[filename];
}

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager instance;
    return instance;
}
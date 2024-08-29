#pragma once

#define SFML_STATIC
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
    static sf::Texture& getTexture(const std::string& filename);
    static sf::Font& getFont(const std::string& filename);

private:
    ResourceManager() = default;  // Private constructor for Singleton
    ~ResourceManager() = default;

    std::unordered_map<std::string, sf::Texture> textures;
    std::unordered_map<std::string, sf::Font> fonts;

    // Singleton instance accessor
    static ResourceManager& getInstance();
};

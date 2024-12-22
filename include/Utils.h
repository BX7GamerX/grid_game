#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <SFML/Graphics.hpp>

// Simple utility namespace
namespace Utils {
    // Save textual grid state, for example
    void saveGridState(const std::vector<std::vector<bool>>& grid, const std::string& filename);

    // Draw text on screen
    void drawText(sf::RenderWindow& window, const sf::Font& font, const std::string& str, float x, float y, unsigned int size=20);
}

#endif // UTILS_H
#ifndef UTILS_H
#define UTILS_H
/**
 * @file Utils.h
 * @brief Utility functions for saving grid states and drawing text.
 */

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

// Simple utility namespace
namespace Utils {
    /**
     * @brief Saves the grid state (1 = road, 0 = empty) to a text file.
     */
    void saveGridState(const std::vector<std::vector<bool>>& grid, const std::string& filename);

    /**
     * @brief Draws text to the window at the specified position.
     */
    void drawText(sf::RenderWindow& window, const sf::Font& font,
                  const std::string& str, float x, float y, unsigned int size=20);
}

#endif // UTILS_H
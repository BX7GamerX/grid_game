#ifndef UI_H
#define UI_H
/**
 * @file UI.h
 * @brief Simple UI helper for drawing buttons and checking clicks.
 */

#include <SFML/Graphics.hpp>
#include <string>

namespace UI {
    /**
     * @brief Draw the given button and text to the window.
     */
    void drawButton(sf::RenderWindow& window,
                    const sf::RectangleShape& shape,
                    const sf::Text& text);

    /**
     * @brief Checks if the button is clicked given a mouse position.
     */
    bool isButtonClicked(const sf::RectangleShape& shape, int mouseX, int mouseY);
}

#endif // UI_H
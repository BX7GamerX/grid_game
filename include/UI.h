#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <string>

namespace UI {
    // Draw a simple rectangle button and text
    void drawButton(sf::RenderWindow& window,
                    const sf::RectangleShape& shape,
                    const sf::Text& text);

    // Check button click
    bool isButtonClicked(const sf::RectangleShape& shape, int mouseX, int mouseY);
}

#endif // UI_H
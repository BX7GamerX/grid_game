#include "UI.h"

namespace UI {
    void drawButton(sf::RenderWindow& window,
                    const sf::RectangleShape& shape,
                    const sf::Text& text) {
        window.draw(shape);
        window.draw(text);
    }

    bool isButtonClicked(const sf::RectangleShape& shape, int mouseX, int mouseY) {
        return shape.getGlobalBounds().contains(static_cast<float>(mouseX),
                                                static_cast<float>(mouseY));
    }
}

#include <SFML/Graphics.hpp>
#include <iostream>
//#include "text.h"

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Grid Game");
    
    // Set framerate limit to 60 FPS
    window.setFramerateLimit(60);
    
    // Create a grid cell shape
    sf::RectangleShape cell(sf::Vector2f(50, 50));
    cell.setFillColor(sf::Color::White);
    cell.setOutlineThickness(1);
    cell.setOutlineColor(sf::Color::Black);

    // Game loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear(sf::Color::Blue);

        // Draw grid
        for (int x = 0; x < 16; x++) {
            for (int y = 0; y < 12; y++) {
                cell.setPosition(x * 50, y * 50);
                window.draw(cell);
            }
        }

        // Display what was drawn
        window.display();
    }

    return 0;
}
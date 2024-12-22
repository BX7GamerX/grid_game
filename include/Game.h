#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "TrafficSignal.h"
#include "Vehicle.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time delta);
    void render();

    sf::RenderWindow m_window;

    Grid* m_grid;
    sf::Texture m_roadTex;
    std::vector<TrafficSignal> m_signals;
    std::vector<Vehicle> m_vehicles;

    // UI placeholders
    sf::RectangleShape m_saveButton, m_validateButton, m_clearButton;
    sf::Font m_font;
    sf::Text m_statusText;
    bool m_mousePressed;
};

#endif // GAME_H

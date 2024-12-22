#pragma once
/**
 * @file Game.h
 * @brief Main game controller class header.
 *
 * The Game class manages the SFML window, UI elements, Grid, and Vehicles.
 * It also handles user input, updates vehicles, checks collisions,
 * and renders all game objects on the screen.
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Grid.h"
#include "Vehicle.h"

class Game {
public:
    /**
     * @brief Construct a new Game object.
     *
     * Initializes the window, loads assets (road texture, font, music),
     * creates the grid, sets up UI buttons, and spawns initial vehicles.
     */
    Game();

    /**
     * @brief Destroy the Game object. Cleans up the grid memory.
     */
    ~Game();

    /**
     * @brief Main loop that handles events, updates objects, and renders.
     */
    void run();

private:
    // Core loop methods
    void processEvents();
    void update(sf::Time delta);
    void render();

    // Collision check among vehicles
    void checkCollisions();

    // SFML Window
    sf::RenderWindow m_window;

    // Music for theme
    sf::Music m_themeMusic;

    // Grid
    Grid* m_grid;
    sf::Texture m_roadTex;

    // UI elements
    sf::RectangleShape m_saveButton;
    sf::RectangleShape m_validateButton;
    sf::RectangleShape m_clearButton;

    sf::Font m_font;
    sf::Text m_saveText;
    sf::Text m_validateText;
    sf::Text m_clearText;
    sf::Text m_statusText;

    // Vehicles
    std::vector<Vehicle> m_vehicles;
    bool m_mousePressed;
};

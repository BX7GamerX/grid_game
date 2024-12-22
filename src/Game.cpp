#include "Game.h"
#include "UI.h"
#include "Utils.h"
#include <iostream>

Game::Game()
: m_window(sf::VideoMode(1020, 800), "GridRoad Clone"), m_mousePressed(false) {
    m_window.setFramerateLimit(60);

    if(!m_roadTex.loadFromFile("assets/roads/road.png")) {
        std::cout << "Warning: road.png not found.\n";
    }
    // Rows, cols, cell size
    m_grid = new Grid(40, 40, 20, m_roadTex);

    // Setup UI
    m_saveButton.setSize(sf::Vector2f(150, 40));
    m_saveButton.setPosition(820.f, 20.f);
    m_saveButton.setFillColor(sf::Color(128,128,128));
    m_validateButton.setSize(sf::Vector2f(150, 40));
    m_validateButton.setPosition(820.f, 80.f);
    m_validateButton.setFillColor(sf::Color(128,128,128));
    m_clearButton.setSize(sf::Vector2f(150,40));
    m_clearButton.setPosition(820.f, 140.f);
    m_clearButton.setFillColor(sf::Color(128,128,128));

    if(!m_font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Font not found.\n";
    }
    m_statusText.setFont(m_font);
    m_statusText.setCharacterSize(18);
    m_statusText.setFillColor(sf::Color::White);
    m_statusText.setPosition(820.f, 200.f);

    // Sample signals and vehicles
    m_signals.push_back(TrafficSignal(500, 500));
    m_vehicles.push_back(Vehicle(100.f, 200.f));
}

void Game::run() {
    sf::Clock clock;
    while(m_window.isOpen()) {
        processEvents();
        sf::Time delta = clock.restart();
        update(delta);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            m_window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            m_mousePressed = true;
            int mx = event.mouseButton.x;
            int my = event.mouseButton.y;
            if(UI::isButtonClicked(m_saveButton, mx, my)) {
                // Save grid state
                // We'll reinterpret the grid's roads into a bool matrix
                // (just for demonstration):
                std::vector<std::vector<bool>> boolGrid(40, std::vector<bool>(40, false));
                for(int r=0; r<40; r++){
                    for(int c=0; c<40; c++){
                        boolGrid[r][c] = m_grid->isRoad(r,c);
                    }
                }
                Utils::saveGridState(boolGrid, "grid_state.txt");
                m_statusText.setString("Grid Saved!");
            } else if(UI::isButtonClicked(m_validateButton, mx, my)) {
                bool connected = m_grid->isAllRoadConnected();
                m_statusText.setString(connected ? "All roads connected!" : "Not fully connected!");
            } else if(UI::isButtonClicked(m_clearButton, mx, my)) {
                // Clear roads
                for(int r=0; r<40; r++){
                    for(int c=0; c<40; c++){
                        m_grid->removeRoad(r,c);
                    }
                }
                m_statusText.setString("Grid Cleared.");
            } else {
                // Place road
                int col = mx / 20; 
                int row = my / 20;
                m_grid->placeRoad(row, col);
            }
        }
        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            m_mousePressed = false;
        }
        if(event.type == sf::Event::MouseMoved && m_mousePressed) {
            int mx = event.mouseMove.x;
            int my = event.mouseMove.y;
            int col = mx / 20; 
            int row = my / 20;
            m_grid->placeRoad(row, col);
        }
    }
}

void Game::update(sf::Time delta) {
    float dt = delta.asSeconds();
    // Update signals
    for(auto &sig : m_signals) {
        sig.update(dt);
    }
    // Update vehicles
    for(auto &veh : m_vehicles) {
        veh.update(dt);
    }
}

void Game::render() {
    m_window.clear(sf::Color(60,60,60));
    // Draw grid
    m_grid->draw(m_window);
    // Draw signals
    for(auto &sig : m_signals) {
        sig.draw(m_window);
    }
    // Draw vehicles
    for(auto &veh : m_vehicles) {
        veh.draw(m_window);
    }
    // Buttons
    UI::drawButton(m_window, m_saveButton, sf::Text("SAVE", m_font, 18));
    UI::drawButton(m_window, m_validateButton, sf::Text("VALIDATE", m_font, 18));
    UI::drawButton(m_window, m_clearButton, sf::Text("CLEAR", m_font, 18));
    // Status
    m_window.draw(m_statusText);
    m_window.display();
}

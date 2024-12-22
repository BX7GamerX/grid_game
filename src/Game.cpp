#include "Game.h"
#include "UI.h"
#include "Grid.h"
#include "Utils.h"
#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime>   // time
#include <cmath>   // sqrt, pow
#include <vector>

Game::Game()
: m_window(sf::VideoMode(1020, 800), "GridRoad Clone"), m_mousePressed(false) {
    srand(static_cast<unsigned int>(time(nullptr))); // Seed RNG

    // Attempt to play theme music
    if(!m_themeMusic.openFromFile("assets/theme.mp3")) {
        std::cout << "Warning: Could not load theme.mp3\n";
    } else {
        m_themeMusic.setLoop(false); // Play once
        m_themeMusic.play();
    }

    // Load the road texture
    if(!m_roadTex.loadFromFile("assets/roads/road.png")) {
        std::cout << "Warning: road.png not found.\n";
    }

    // Create grid
    m_grid = new Grid(40, 40, 20, m_roadTex);

    // Optionally load a previously saved grid state
    if(!m_grid->loadGridState("grid_state.txt")) {
        std::cout << "No valid grid_state.txt found, using blank.\n";
    }

    // Initialize road edges for spawns
    m_grid->initializeEdgeRoads();

    // Set up UI buttons
    m_saveButton.setSize(sf::Vector2f(150.f, 40.f));
    m_saveButton.setPosition(820.f, 20.f);
    m_saveButton.setFillColor(sf::Color(128,128,128));

    m_validateButton.setSize(sf::Vector2f(150.f, 40.f));
    m_validateButton.setPosition(820.f, 80.f);
    m_validateButton.setFillColor(sf::Color(128,128,128));

    m_clearButton.setSize(sf::Vector2f(150.f, 40.f));
    m_clearButton.setPosition(820.f, 140.f);
    m_clearButton.setFillColor(sf::Color(128,128,128));

    // Load font
    if(!m_font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        std::cout << "Warning: Font not found.\n";
    }

    // Configure button text with center alignment
    m_saveText.setFont(m_font);
    m_saveText.setString("SAVE");
    m_saveText.setCharacterSize(18);
    {
        sf::FloatRect b = m_saveText.getLocalBounds();
        m_saveText.setOrigin(b.left + b.width/2.f, b.top + b.height/2.f);
        m_saveText.setPosition(
            m_saveButton.getPosition().x + m_saveButton.getSize().x/2.f,
            m_saveButton.getPosition().y + m_saveButton.getSize().y/2.f
        );
    }

    m_validateText.setFont(m_font);
    m_validateText.setString("VALIDATE");
    m_validateText.setCharacterSize(18);
    {
        sf::FloatRect b = m_validateText.getLocalBounds();
        m_validateText.setOrigin(b.left + b.width/2.f, b.top + b.height/2.f);
        m_validateText.setPosition(
            m_validateButton.getPosition().x + m_validateButton.getSize().x/2.f,
            m_validateButton.getPosition().y + m_validateButton.getSize().y/2.f
        );
    }

    m_clearText.setFont(m_font);
    m_clearText.setString("CLEAR");
    m_clearText.setCharacterSize(18);
    {
        sf::FloatRect b = m_clearText.getLocalBounds();
        m_clearText.setOrigin(b.left + b.width/2.f, b.top + b.height/2.f);
        m_clearText.setPosition(
            m_clearButton.getPosition().x + m_clearButton.getSize().x/2.f,
            m_clearButton.getPosition().y + m_clearButton.getSize().y/2.f
        );
    }

    m_statusText.setFont(m_font);
    m_statusText.setCharacterSize(18);
    m_statusText.setFillColor(sf::Color::White);
    m_statusText.setPosition(820.f, 200.f);

    // Spawn a test vehicle from the left edge to an arbitrary destination
    // More vehicles can be spawned similarly (one for each edge).
    m_vehicles.emplace_back(0.f + m_grid->getCellSize()*0.5f,
                            (m_grid->getRows()/2) * m_grid->getCellSize() + m_grid->getCellSize()*0.5f,
                            m_grid);
    // Destination is the right edge
    m_vehicles.back().setDestination(
        m_grid->getCols()*m_grid->getCellSize() - m_grid->getCellSize()*0.5f,
        (m_grid->getRows()/2) * m_grid->getCellSize() + m_grid->getCellSize()*0.5f
    );
}

Game::~Game() {
    delete m_grid;
}

void Game::run() {
    sf::Clock clock;
    while(m_window.isOpen()) {
        processEvents();
        sf::Time dt = clock.restart();
        update(dt);
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
                // Save grid
                std::vector<std::vector<bool>> boolGrid(m_grid->getRows(), std::vector<bool>(m_grid->getCols(), false));
                for(int r=0; r<m_grid->getRows(); r++){
                    for(int c=0; c<m_grid->getCols(); c++){
                        boolGrid[r][c] = m_grid->isRoad(r,c);
                    }
                }
                Utils::saveGridState(boolGrid, "grid_state.txt");
                m_statusText.setString("Grid Saved!");
            }
            else if(UI::isButtonClicked(m_validateButton, mx, my)) {
                // Check connectivity
                bool connected = m_grid->isAllRoadConnected();
                m_statusText.setString(connected ? "All roads connected!" : "Not fully connected!");
            }
            else if(UI::isButtonClicked(m_clearButton, mx, my)) {
                // Clear roads
                for(int r=0; r<m_grid->getRows(); r++){
                    for(int c=0; c<m_grid->getCols(); c++){
                        m_grid->removeRoad(r,c);
                    }
                }
                m_statusText.setString("Grid Cleared.");
            }
            else {
                // Place road tile
                int col = mx / m_grid->getCellSize();
                int row = my / m_grid->getCellSize();
                m_grid->placeRoad(row, col);
            }
        }
        if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            m_mousePressed = false;
        }
        if(event.type == sf::Event::MouseMoved && m_mousePressed) {
            // Drag to place roads
            int mx = event.mouseMove.x;
            int my = event.mouseMove.y;
            int col = mx / m_grid->getCellSize();
            int row = my / m_grid->getCellSize();
            m_grid->placeRoad(row, col);
        }
    }
}

void Game::update(sf::Time delta) {
    // Update vehicles
    for(auto &veh : m_vehicles) {
        veh.update(delta.asSeconds());
    }

    // Check collisions
    checkCollisions();

    // Remove vehicles that reached destination
    auto it = m_vehicles.begin();
    while(it != m_vehicles.end()) {
        if(it->hasArrived()) {
            it = m_vehicles.erase(it);
        } else {
            ++it;
        }
    }
}

void Game::render() {
    m_window.clear(sf::Color(60,60,60));

    // Draw grid
    m_grid->draw(m_window);

    // Draw vehicles
    for(auto &veh : m_vehicles) {
        veh.draw(m_window);
    }

    // Draw UI
    UI::drawButton(m_window, m_saveButton, m_saveText);
    UI::drawButton(m_window, m_validateButton, m_validateText);
    UI::drawButton(m_window, m_clearButton, m_clearText);
    m_window.draw(m_statusText);

    m_window.display();
}

void Game::checkCollisions() {
    // Very basic collision check: if two vehicles are too close,
    // the one behind stops temporarily. This is a simplistic
    // approach for demonstration.
    for(size_t i=0; i<m_vehicles.size(); i++) {
        for(size_t j=i+1; j<m_vehicles.size(); j++) {
            float dx = m_vehicles[i].getPosition().x - m_vehicles[j].getPosition().x;
            float dy = m_vehicles[i].getPosition().y - m_vehicles[j].getPosition().y;
            float distSq = dx*dx + dy*dy;
            // If vehicles are within 20 px
            if(distSq < 400.0f) {
                // Stop one of them arbitrarily
                m_vehicles[j].forceStop();
            }
        }
    }
}

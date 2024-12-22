#include "Vehicle.h"

Vehicle::Vehicle(float x, float y, Grid* grid)
: m_position(x, y), m_velocity(40.f, 0.f), m_grid(grid) {
    m_shape.setRadius(8.f);
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setPosition(m_position);
}

void Vehicle::update(float deltaTime) {
    if(!m_grid) return;

    // Predict next position
    sf::Vector2f nextPos = m_position + m_velocity * deltaTime;
    int nextCol = static_cast<int>(nextPos.x / m_grid->getCellSize());
    int nextRow = static_cast<int>(nextPos.y / m_grid->getCellSize());

    // If next tile is road, move; otherwise, stop
    if(m_grid->isRoad(nextRow, nextCol)) {
        m_position = nextPos;
        m_shape.setPosition(m_position);
    } else {
        m_velocity = sf::Vector2f(0.f, 0.f); 
    }
}

void Vehicle::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}
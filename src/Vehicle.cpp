#include "Vehicle.h"
#include <cmath>
#include <iostream>

Vehicle::Vehicle(float x, float y, Grid* grid)
: m_position(x, y),
  m_velocity(0.f, 0.f),
  m_destination(x, y),
  m_arrived(false),
  m_speed(40.f),
  m_grid(grid)
{
    // Simple circle for visual representation
    m_shape.setRadius(8.f);
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setOrigin(8.f, 8.f); // center the circle
    m_shape.setPosition(m_position);
}

void Vehicle::setDestination(float x, float y) {
    m_destination = sf::Vector2f(x, y);
    m_arrived = false;
}

bool Vehicle::hasArrived() const {
    return m_arrived;
}

sf::Vector2f Vehicle::getPosition() const {
    return m_position;
}

void Vehicle::forceStop() {
    m_velocity.x = 0.f;
    m_velocity.y = 0.f;
}

void Vehicle::update(float deltaTime) {
    if(!m_grid) return;

    // If arrived, do nothing
    if(m_arrived) return;

    // Direction to destination
    float dx = m_destination.x - m_position.x;
    float dy = m_destination.y - m_position.y;
    float distSq = dx*dx + dy*dy;

    // If close enough, mark arrived
    if(distSq < 10.f) {
        m_arrived = true;
        return;
    }

    // Normalize direction
    float dist = std::sqrt(distSq);
    float dirX = dx / dist;
    float dirY = dy / dist;

    // Proposed new position
    sf::Vector2f nextPos = m_position + sf::Vector2f(dirX*m_speed, dirY*m_speed) * deltaTime;

    // Determine next tile
    int nextCol = static_cast<int>(nextPos.x / m_grid->getCellSize());
    int nextRow = static_cast<int>(nextPos.y / m_grid->getCellSize());

    // If next cell is road, proceed; else, remain in place
    if(m_grid->isRoad(nextRow, nextCol)) {
        m_position = nextPos;
    } else {
        // Could optionally try different routes, but here we just stop if blocked
        forceStop();
    }

    // Ensure vehicle remains within grid bounds
    clampPosition();

    // Update shape
    m_shape.setPosition(m_position);
}

void Vehicle::clampPosition() {
    // Prevent going below or beyond the grid edges
    float halfCell = m_grid->getCellSize() * 0.5f;
    float maxX = (m_grid->getCols() * m_grid->getCellSize()) - halfCell;
    float maxY = (m_grid->getRows() * m_grid->getCellSize()) - halfCell;

    if(m_position.x < halfCell) m_position.x = halfCell;
    if(m_position.y < halfCell) m_position.y = halfCell;
    if(m_position.x > maxX)     m_position.x = maxX;
    if(m_position.y > maxY)     m_position.y = maxY;
}

void Vehicle::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}
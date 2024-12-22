#include "Vehicle.h"

Vehicle::Vehicle(float x, float y)
: m_position(x, y), m_velocity(40.f,0.f) {
    m_shape.setRadius(8.f);
    m_shape.setFillColor(sf::Color::Blue);
    m_shape.setPosition(m_position);
}

void Vehicle::update(float deltaTime) {
    // Simplified movement
    m_position += m_velocity * deltaTime;
    m_shape.setPosition(m_position);
}

void Vehicle::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}
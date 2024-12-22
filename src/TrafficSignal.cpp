#include "TrafficSignal.h"

TrafficSignal::TrafficSignal(int x, int y)
: m_state(0), m_timer(0.0f), m_cycleTime(6.0f) {
    m_shape.setSize(sf::Vector2f(20, 60));
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(static_cast<float>(x), static_cast<float>(y));
}

void TrafficSignal::update(float deltaTime) {
    m_timer += deltaTime;
    float phase = m_cycleTime / 3.0f; 
    if(m_timer >= m_cycleTime) {
        m_timer = 0.0f;
        m_state = 0;
        m_shape.setFillColor(sf::Color::Red);
    } else if(m_timer >= 2 * phase) {
        m_state = 2; // Yellow
        m_shape.setFillColor(sf::Color::Yellow);
    } else if(m_timer >= phase) {
        m_state = 1; // Green
        m_shape.setFillColor(sf::Color::Green);
    } else {
        m_state = 0; // Red
        m_shape.setFillColor(sf::Color::Red);
    }
}

void TrafficSignal::draw(sf::RenderWindow& window) {
    window.draw(m_shape);
}

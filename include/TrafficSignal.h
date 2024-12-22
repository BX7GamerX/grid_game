#ifndef TRAFFICSIGNAL_H
#define TRAFFICSIGNAL_H

#include <SFML/Graphics.hpp>

class TrafficSignal {
public:
    TrafficSignal(int x, int y);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    // Simplified states: 0 = Red, 1 = Green, 2 = Yellow
    int m_state;
    float m_timer;
    const float m_cycleTime; // total cycle duration
    sf::RectangleShape m_shape;
};

#endif // TRAFFICSIGNAL_H
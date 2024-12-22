#ifndef VEHICLE_H
#define VEHICLE_H

#include <SFML/Graphics.hpp>

class Vehicle {
public:
    Vehicle(float x, float y);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::CircleShape m_shape; 
};

#endif // VEHICLE_H
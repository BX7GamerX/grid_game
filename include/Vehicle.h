#ifndef VEHICLE_H
#define VEHICLE_H
/**
 * @file Vehicle.h
 * @brief Represents a moving vehicle on the grid.
 *
 * A Vehicle knows its position, velocity, and directional movement.
 * It checks the Grid for valid roads and tries to reach a destination cell,
 * despawning upon arrival. Simple collision logic can stop it temporarily.
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include "Grid.h"

class Vehicle {
public:
    /**
     * @brief Construct a new Vehicle object.
     * @param x Initial x-position in pixels
     * @param y Initial y-position in pixels
     * @param grid Pointer to the Grid object for road checking
     */
    Vehicle(float x, float y, Grid* grid);

    /**
     * @brief Update the vehicle's position and direction.
     * @param deltaTime Time since last update (in seconds).
     */
    void update(float deltaTime);

    /**
     * @brief Render the vehicle in the given window.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Set the target destination in pixel coordinates.
     */
    void setDestination(float x, float y);

    /**
     * @brief Returns true if the vehicle has arrived at its destination.
     */
    bool hasArrived() const;

    /**
     * @brief Returns the current position of the vehicle.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Force the vehicle to stop (used in collision).
     */
    void forceStop();

private:
    sf::Vector2f m_position;   ///< Current position in world space
    sf::Vector2f m_velocity;   ///< Current velocity in px/s
    sf::Vector2f m_destination;///< Target location
    bool m_arrived;            ///< True if the Vehicle has reached destination
    float m_speed;             ///< Movement speed in px/s

    sf::CircleShape m_shape; 
    Grid* m_grid; // For road checks

    // Private helper to clamp position within the grid
    void clampPosition();
};

#endif // VEHICLE_H
#ifndef GRID_H
#define GRID_H
/**
 * @file Grid.h
 * @brief Manages a grid of tiles, which can be Road or Empty.
 *
 * The Grid class stores all tiles, handles road placement/removal,
 * loads saved states, and checks connectivity. Also draws itself.
 */

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum class TileType {
    Empty,
    Road
};

class Grid {
public:
    /**
     * @brief Construct a new Grid object.
     * @param rows Number of rows
     * @param cols Number of columns
     * @param cellSize Size of each cell in pixels
     * @param roadTexture Reference to an SFML Texture for road rendering
     */
    Grid(int rows, int cols, int cellSize, const sf::Texture& roadTexture);

    /**
     * @brief Places a road tile at (r, c).
     */
    void placeRoad(int r, int c);

    /**
     * @brief Removes a road tile at (r, c).
     */
    void removeRoad(int r, int c);

    /**
     * @brief Checks if tile (r, c) is a road.
     */
    bool isRoad(int r, int c) const;

    /**
     * @brief Checks if all road tiles are connected using BFS.
     */
    bool isAllRoadConnected() const;

    /**
     * @brief Draws the grid (and roads) on the window.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Loads a grid state from file (user-saved).
     * @return true if loaded, false if file not found.
     */
    bool loadGridState(const std::string& filename);

    /**
     * @brief Places roads around the edges of the map for spawning.
     */
    void initializeEdgeRoads();

    // Getters for grid dimensions
    int getCellSize() const { return m_cellSize; }
    int getRows() const { return m_rows; }
    int getCols() const { return m_cols; }

private:
    int m_rows;
    int m_cols;
    int m_cellSize;
    const sf::Texture& m_roadTexture;
    std::vector<std::vector<TileType>> m_tiles;
};

#endif // GRID_H
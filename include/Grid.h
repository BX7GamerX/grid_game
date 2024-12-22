#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>

enum class TileType {
    Empty,
    Road
};

class Grid {
public:
    Grid(int rows, int cols, int cellSize, const sf::Texture& roadTexture);

    void placeRoad(int r, int c);
    void removeRoad(int r, int c);
    bool isRoad(int r, int c) const;

    // BFS-based connectivity check
    bool isAllRoadConnected() const;

    void draw(sf::RenderWindow& window);

private:
    int m_rows;
    int m_cols;
    int m_cellSize;
    const sf::Texture& m_roadTexture;
    std::vector<std::vector<TileType>> m_tiles;
};

#endif // GRID_H
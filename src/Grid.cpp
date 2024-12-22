#include "Grid.h"
#include <queue>
#include <iostream>

Grid::Grid(int rows, int cols, int cellSize, const sf::Texture& roadTexture)
: m_rows(rows), m_cols(cols), m_cellSize(cellSize), m_roadTexture(roadTexture) {
    m_tiles.resize(m_rows, std::vector<TileType>(m_cols, TileType::Empty));
}

void Grid::placeRoad(int r, int c) {
    if(r >= 0 && r < m_rows && c >= 0 && c < m_cols) {
        m_tiles[r][c] = TileType::Road;
    }
}

void Grid::removeRoad(int r, int c) {
    if(r >= 0 && r < m_rows && c >= 0 && c < m_cols) {
        m_tiles[r][c] = TileType::Empty;
    }
}

bool Grid::isRoad(int r, int c) const {
    if(r < 0 || r >= m_rows || c < 0 || c >= m_cols) return false;
    return (m_tiles[r][c] == TileType::Road);
}

bool Grid::isAllRoadConnected() const {
    // Find a starting road cell
    int startR = -1, startC = -1;
    for(int r = 0; r < m_rows; r++){
        for(int c = 0; c < m_cols; c++){
            if(m_tiles[r][c] == TileType::Road) {
                startR = r; startC = c;
                break;
            }
        }
        if(startR != -1) break;
    }
    // No roads found => trivially "connected"
    if(startR == -1) return true;

    // BFS
    std::vector<std::vector<bool>> visited(m_rows, std::vector<bool>(m_cols, false));
    std::queue<std::pair<int,int>> q;
    q.push({startR, startC});
    visited[startR][startC] = true;

    // Count total road cells
    int totalRoad = 0;
    for(int rr = 0; rr < m_rows; rr++){
        for(int cc = 0; cc < m_cols; cc++){
            if(m_tiles[rr][cc] == TileType::Road) totalRoad++;
        }
    }

    int roadCount = 0;
    const int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while(!q.empty()){
        auto [rr, cc] = q.front(); 
        q.pop();
        roadCount++;
        for(auto &d : dirs){
            int nr = rr + d[0];
            int nc = cc + d[1];
            if(nr >= 0 && nr < m_rows && nc >= 0 && nc < m_cols){
                if(m_tiles[nr][nc] == TileType::Road && !visited[nr][nc]){
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }
    return (roadCount == totalRoad);
}

void Grid::draw(sf::RenderWindow& window) {
    sf::RectangleShape cellShape(sf::Vector2f(m_cellSize - 1, m_cellSize - 1));
    for(int r=0; r<m_rows; r++){
        for(int c=0; c<m_cols; c++){
            int x = c * m_cellSize;
            int y = r * m_cellSize;
            if(m_tiles[r][c] == TileType::Road && m_roadTexture.getSize().x != 0) {
                sf::Sprite roadSprite(m_roadTexture);
                roadSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
                roadSprite.setScale(
                    static_cast<float>(m_cellSize)/m_roadTexture.getSize().x,
                    static_cast<float>(m_cellSize)/m_roadTexture.getSize().y
                );
                window.draw(roadSprite);
            } else {
                cellShape.setPosition(static_cast<float>(x), static_cast<float>(y));
                cellShape.setFillColor(
                    (m_tiles[r][c] == TileType::Road) ? sf::Color::Black : sf::Color::White
                );
                window.draw(cellShape);
            }
        }
    }
}

#include "Grid.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <string>

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
    if(r < 0 || r >= m_rows || c < 0 || c >= m_cols) 
        return false;
    return (m_tiles[r][c] == TileType::Road);
}

bool Grid::isAllRoadConnected() const {
    // Find first road cell
    int startR = -1, startC = -1;
    for(int r=0; r<m_rows; r++){
        for(int c=0; c<m_cols; c++){
            if(isRoad(r,c)) {
                startR = r;
                startC = c;
                break;
            }
        }
        if(startR != -1) break;
    }

    // If no roads, trivially connected
    if(startR == -1) return true;

    // BFS
    std::vector<std::vector<bool>> visited(m_rows, std::vector<bool>(m_cols, false));
    std::queue<std::pair<int,int>> q;
    visited[startR][startC] = true;
    q.push({startR, startC});

    // Count total road cells
    int totalRoad = 0;
    for(int rr=0; rr<m_rows; rr++){
        for(int cc=0; cc<m_cols; cc++){
            if(isRoad(rr, cc)) {
                totalRoad++;
            }
        }
    }

    int roadCount = 0;
    const int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while(!q.empty()) {
        auto [rr, cc] = q.front();
        q.pop();
        roadCount++;

        for(auto &d : dirs) {
            int nr = rr + d[0];
            int nc = cc + d[1];
            if(nr >= 0 && nr < m_rows && nc >= 0 && nc < m_cols) {
                if(isRoad(nr, nc) && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
    }
    return (roadCount == totalRoad);
}

bool Grid::loadGridState(const std::string& filename) {
    std::ifstream inFile(filename);
    if(!inFile.is_open()) {
        std::cout << "Error: Unable to open " << filename << "\n";
        return false;
    }

    std::string line;
    int row = 0;
    while(std::getline(inFile, line)) {
        // Ignore very short or commented lines
        if(line.size() < 2 || line[0] == '/') 
            continue;
        for(int c = 0; c < m_cols && c < (int)line.size(); c++) {
            if(line[c] == '1') {
                m_tiles[row][c] = TileType::Road;
            } else {
                m_tiles[row][c] = TileType::Empty;
            }
        }
        row++;
        if(row >= m_rows) break;
    }

    inFile.close();
    std::cout << "Loaded grid from " << filename << "\n";
    return true;
}

void Grid::draw(sf::RenderWindow& window) {
    // Slight offset so roads are contiguous
    sf::RectangleShape cellShape(sf::Vector2f((float)m_cellSize - 1.f, (float)m_cellSize - 1.f));

    for(int r=0; r<m_rows; r++){
        for(int c=0; c<m_cols; c++){
            int x = c * m_cellSize;
            int y = r * m_cellSize;

            if(m_tiles[r][c] == TileType::Road && m_roadTexture.getSize().x != 0) {
                // Draw road sprite
                sf::Sprite roadSprite(m_roadTexture);
                roadSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
                roadSprite.setScale(
                    static_cast<float>(m_cellSize)/m_roadTexture.getSize().x,
                    static_cast<float>(m_cellSize)/m_roadTexture.getSize().y
                );
                window.draw(roadSprite);
            } else {
                // Draw empty tile
                cellShape.setPosition(static_cast<float>(x),  static_cast<float>(y));
                cellShape.setFillColor((m_tiles[r][c] == TileType::Road) 
                                       ? sf::Color::Black 
                                       : sf::Color::White);
                window.draw(cellShape);
            }
        }
    }
}

void Grid::initializeEdgeRoads() {
    // Automatically place roads on all four edges to allow spawn from edges
    // Top & Bottom rows
    for(int c=0; c<m_cols; c++){
        m_tiles[0][c] = TileType::Road;
        m_tiles[m_rows-1][c] = TileType::Road;
    }
    // Left & Right columns
    for(int r=0; r<m_rows; r++){
        m_tiles[r][0] = TileType::Road;
        m_tiles[r][m_cols-1] = TileType::Road;
    }
}

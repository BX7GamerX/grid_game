#include "Utils.h"
#include <fstream>
#include <vector>
#include <iostream>
namespace Utils {
    void saveGridState(const std::vector<std::vector<bool>>& grid, const std::string& filename) {
        std::ofstream outFile(filename);
        if(!outFile.is_open()) {
            std::cout << "Error: Unable to open " << filename << " for writing.\n";
            return;
        }
        for(const auto& row : grid) {
            for(bool road : row) {
                outFile << (road ? '1' : '0');
            }
            outFile << "\n";
        }
        outFile.close();
        std::cout << "Grid state saved to " << filename << "\n";
    }

    void drawText(sf::RenderWindow& window, const sf::Font& font,
                  const std::string& str, float x, float y, unsigned int size) {
        sf::Text text(str, font, size);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
        window.draw(text);
    }
}
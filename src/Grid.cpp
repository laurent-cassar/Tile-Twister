#include "Grid.hpp"
#include <random>
#include <algorithm>

Grid::Grid() : score_(0), won_(false) {
    reset();
}

void Grid::reset() {
    for (auto& row : cells_) {
        row.fill(0);
    }
    score_ = 0;
    won_ = false;
    addRandomTile();
    addRandomTile();
}

void Grid::addRandomTile() {
    std::vector<std::pair<int, int>> emptyCells;
    
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (cells_[i][j] == 0) {
                emptyCells.push_back({i, j});
            }
        }
    }
    
    if (!emptyCells.empty()) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        
        std::uniform_int_distribution<> posDist(0, emptyCells.size() - 1);
        std::uniform_real_distribution<> valDist(0.0, 1.0);
        
        auto [row, col] = emptyCells[posDist(gen)];
        cells_[row][col] = (valDist(gen) < 0.9) ? 2 : 4;
    }
}

bool Grid::moveLeft() {
    bool moved = false;
    
    for (int i = 0; i < SIZE; ++i) {
        std::vector<int> row;
        
        // Filtrer les cellules non vides
        for (int j = 0; j < SIZE; ++j) {
            if (cells_[i][j] != 0) {
                row.push_back(cells_[i][j]);
            }
        }
        
        // Fusionner les tuiles adjacentes identiques
        std::vector<int> merged;
        for (size_t j = 0; j < row.size(); ++j) {
            if (j < row.size() - 1 && row[j] == row[j + 1]) {
                int mergedValue = row[j] * 2;
                merged.push_back(mergedValue);
                score_ += mergedValue;
                if (mergedValue == 2048) won_ = true;
                ++j;
            } else {
                merged.push_back(row[j]);
            }
        }
        
        // Remplir la ligne
        for (int j = 0; j < SIZE; ++j) {
            int newValue = (j < merged.size()) ? merged[j] : 0;
            if (cells_[i][j] != newValue) {
                moved = true;
            }
            cells_[i][j] = newValue;
        }
    }
    
    if (moved) {
        addRandomTile();
    }
    
    return moved;
}

bool Grid::moveRight() {
    rotateCW();
    rotateCW();
    bool moved = moveLeft();
    rotateCW();
    rotateCW();
    return moved;
}

bool Grid::moveUp() {
    rotateCCW();
    bool moved = moveLeft();
    rotateCW();
    return moved;
}

bool Grid::moveDown() {
    rotateCW();
    bool moved = moveLeft();
    rotateCCW();
    return moved;
}

void Grid::rotateCW() {
    std::array<std::array<int, SIZE>, SIZE> temp;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[j][SIZE - 1 - i] = cells_[i][j];
        }
    }
    cells_ = temp;
}

void Grid::rotateCCW() {
    std::array<std::array<int, SIZE>, SIZE> temp;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            temp[SIZE - 1 - j][i] = cells_[i][j];
        }
    }
    cells_ = temp;
}

bool Grid::canMove() const {
    // Vérifier s'il y a des cellules vides
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (cells_[i][j] == 0) return true;
        }
    }
    
    // Vérifier s'il y a des fusions possibles
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (j < SIZE - 1 && cells_[i][j] == cells_[i][j + 1]) return true;
            if (i < SIZE - 1 && cells_[i][j] == cells_[i + 1][j]) return true;
        }
    }
    
    return false;
}

int Grid::getCell(int row, int col) const {
    return cells_[row][col];
}

void Grid::setCell(int row, int col, int value) {
    cells_[row][col] = value;
}
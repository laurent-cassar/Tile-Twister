#include "../include/Grid.hpp"
#include <cassert>
#include <iostream>

void testGridInitialization() {
    Grid grid;
    int tileCount = 0;
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            if (grid.getCell(i, j) != 0) {
                tileCount++;
            }
        }
    }
    
    assert(tileCount == 2);
    std::cout << "✓ Test initialisation réussi" << std::endl;
}

void testMoveLeft() {
    Grid grid;
    grid.reset();
    
    // Configuration manuelle
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    grid.setCell(0, 2, 2);
    grid.setCell(0, 3, 2);
    
    grid.moveLeft();
    
    assert(grid.getCell(0, 0) == 4);
    std::cout << "✓ Test déplacement gauche réussi" << std::endl;
}

int main() {
    testGridInitialization();
    testMoveLeft();
    
    std::cout << "✅ Tous les tests réussis!" << std::endl;
    return 0;
}
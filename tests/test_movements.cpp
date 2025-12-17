#include "../include/Grid.hpp"
#include <cassert>
#include <iostream>

void testMoveLeftSimple() {
    Grid grid;
    
    // Configuration initiale
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    grid.setCell(0, 2, 2);
    grid.setCell(0, 3, 2);
    
    grid.moveLeft();
    
    // Après le mouvement, les deux 2 devraient avoir fusionné en 4 à gauche
    assert(grid.getCell(0, 0) == 4);
    std::cout << "✓ Test déplacement gauche simple réussi" << std::endl;
}

void testMoveRightSimple() {
    Grid grid;
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    grid.setCell(0, 0, 2);
    grid.setCell(0, 1, 2);
    
    grid.moveRight();
    
    assert(grid.getCell(0, 3) == 4);
    std::cout << "✓ Test déplacement droite simple réussi" << std::endl;
}

void testMoveUpSimple() {
    Grid grid;
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    grid.setCell(2, 0, 2);
    grid.setCell(3, 0, 2);
    
    grid.moveUp();
    
    assert(grid.getCell(0, 0) == 4);
    std::cout << "✓ Test déplacement haut simple réussi" << std::endl;
}

void testMoveDownSimple() {
    Grid grid;
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    grid.setCell(0, 0, 2);
    grid.setCell(1, 0, 2);
    
    grid.moveDown();
    
    assert(grid.getCell(3, 0) == 4);
    std::cout << "✓ Test déplacement bas simple réussi" << std::endl;
}

void testMultipleMerges() {
    Grid grid;
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    // Ligne avec plusieurs fusions possibles: 2 2 2 2
    grid.setCell(0, 0, 2);
    grid.setCell(0, 1, 2);
    grid.setCell(0, 2, 2);
    grid.setCell(0, 3, 2);
    
    grid.moveLeft();
    
    // Devrait donner: 4 4 0 0
    assert(grid.getCell(0, 0) == 4);
    assert(grid.getCell(0, 1) == 4);
    assert(grid.getCell(0, 2) == 0 || grid.getCell(0, 2) == 2); // Nouvelle tuile aléatoire
    std::cout << "✓ Test fusions multiples réussi" << std::endl;
}

void testNoMergeOnDifferentValues() {
    Grid grid;
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    grid.setCell(0, 0, 2);
    grid.setCell(0, 1, 4);
    
    grid.moveLeft();
    
    // Les tuiles devraient rester séparées
    assert(grid.getCell(0, 0) == 2);
    assert(grid.getCell(0, 1) == 4);
    std::cout << "✓ Test pas de fusion sur valeurs différentes réussi" << std::endl;
}

void testComplexMovement() {
    Grid grid;
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    // Configuration: 0 2 2 4
    grid.setCell(0, 1, 2);
    grid.setCell(0, 2, 2);
    grid.setCell(0, 3, 4);
    
    grid.moveLeft();
    
    // Résultat attendu: 4 4 0 0 (ou 2/4 si nouvelle tuile)
    assert(grid.getCell(0, 0) == 4);
    assert(grid.getCell(0, 1) == 4 || grid.getCell(0, 1) == 2); // Peut être nouvelle tuile
    std::cout << "✓ Test mouvement complexe réussi" << std::endl;
}

void testScoreCalculation() {
    Grid grid;
    grid.reset();
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
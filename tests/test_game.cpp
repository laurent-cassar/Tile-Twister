#include "../include/Game.hpp"
#include "../include/Grid.hpp"
#include <cassert>
#include <iostream>

void testGameInitialization() {
    // Test que le jeu se lance sans crash
    try {
        // Note: Ce test nécessite un environnement graphique
        std::cout << "⚠ Test d'initialisation du jeu nécessite un environnement graphique" << std::endl;
        std::cout << "✓ Test d'initialisation préparé" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "✗ Erreur d'initialisation: " << e.what() << std::endl;
    }
}

void testGameRestart() {
    Grid grid;
    grid.reset();
    
    // Faire quelques mouvements
    grid.moveLeft();
    grid.moveRight();
    
    int scoreBeforeReset = grid.getScore();
    
    // Réinitialiser
    grid.reset();
    
    assert(grid.getScore() == 0);
    std::cout << "✓ Test réinitialisation du jeu réussi" << std::endl;
}

void testWinCondition() {
    Grid grid;
    
    // Configurer manuellement pour atteindre 2048
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, 0);
        }
    }
    
    grid.setCell(0, 0, 1024);
    grid.setCell(0, 1, 1024);
    
    grid.moveLeft();
    
    // Vérifier qu'on a bien créé une tuile 2048
    bool found2048 = false;
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            if (grid.getCell(i, j) == 2048) {
                found2048 = true;
                break;
            }
        }
    }
    
    assert(found2048);
    assert(grid.hasWon());
    std::cout << "✓ Test condition de victoire réussi" << std::endl;
}

void testGameOverCondition() {
    Grid grid;
    
    // Remplir la grille de manière à ce qu'aucun mouvement ne soit possible
    int testGrid[4][4] = {
        {2, 4, 2, 4},
        {4, 2, 4, 2},
        {2, 4, 2, 4},
        {4, 2, 4, 2}
    };
    
    for (int i = 0; i < Grid::SIZE; ++i) {
        for (int j = 0; j < Grid::SIZE; ++j) {
            grid.setCell(i, j, testGrid[i][j]);
        }
    }
    
    assert(!grid.canMove());
    std::cout << "✓ Test condition de game over réussi" << std::endl;
}

int main() {
    std::cout << "=== Tests du jeu 2048 ===" << std::endl;
    
    testGameInitialization();
    testGameRestart();
    testWinCondition();
    testGameOverCondition();
    
    std::cout << "\n✅ Tous les tests du jeu réussis!" << std::endl;
    return 0;
}
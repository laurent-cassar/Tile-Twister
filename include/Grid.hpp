#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <array>

class Grid {
public:
    static constexpr int SIZE = 4;
    
    Grid();
    void reset();
    void addRandomTile();
    bool canMove() const;
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    
    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);
    
    int getScore() const { return score_; }
    bool hasWon() const { return won_; }
    
private:
    std::array<std::array<int, SIZE>, SIZE> cells_;
    int score_;
    bool won_;
    
    bool move(int dx, int dy);
    void rotateCW();
    void rotateCCW();
};

#endif
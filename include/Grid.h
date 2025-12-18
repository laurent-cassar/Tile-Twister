#pragma once

class Grid
{
public:
    static const int SIZE = 4;
    int cells[SIZE][SIZE];

    Grid();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    void addRandomTile();
};
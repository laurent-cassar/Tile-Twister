#include "Grid.h"
#include <cstdlib>
#include <vector>

Grid::Grid()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            cells[i][j] = 0;

    addRandomTile();
    addRandomTile();
}

void Grid::addRandomTile()
{
    std::vector<std::pair<int, int>> empty;

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (cells[i][j] == 0)
                empty.push_back({i, j});

    if (!empty.empty())
    {
        auto [x, y] = empty[rand() % empty.size()];
        cells[x][y] = (rand() % 10 == 0) ? 4 : 2;
    }
}

bool Grid::moveLeft()
{
    bool moved = false;

    for (int i = 0; i < SIZE; i++)
    {
        int lastMerge = -1;
        for (int j = 1; j < SIZE; j++)
        {
            if (cells[i][j] == 0)
                continue;

            int k = j;
            while (k > 0 && cells[i][k - 1] == 0)
            {
                cells[i][k - 1] = cells[i][k];
                cells[i][k] = 0;
                k--;
                moved = true;
            }

            if (k > 0 && cells[i][k - 1] == cells[i][k] && lastMerge != k - 1)
            {
                cells[i][k - 1] *= 2;
                cells[i][k] = 0;
                lastMerge = k - 1;
                moved = true;
            }
        }
    }
    return moved;
}

bool Grid::moveRight()
{
    bool moved = false;

    for (int i = 0; i < SIZE; i++)
    {
        int lastMerge = -1;
        for (int j = SIZE - 2; j >= 0; j--)
        {
            if (cells[i][j] == 0)
                continue;

            int k = j;
            while (k < SIZE - 1 && cells[i][k + 1] == 0)
            {
                cells[i][k + 1] = cells[i][k];
                cells[i][k] = 0;
                k++;
                moved = true;
            }

            if (k < SIZE - 1 && cells[i][k + 1] == cells[i][k] && lastMerge != k + 1)
            {
                cells[i][k + 1] *= 2;
                cells[i][k] = 0;
                lastMerge = k + 1;
                moved = true;
            }
        }
    }
    return moved;
}

bool Grid::moveUp()
{
    bool moved = false;

    for (int j = 0; j < SIZE; j++)
    {
        int lastMerge = -1;
        for (int i = 1; i < SIZE; i++)
        {
            if (cells[i][j] == 0)
                continue;

            int k = i;
            while (k > 0 && cells[k - 1][j] == 0)
            {
                cells[k - 1][j] = cells[k][j];
                cells[k][j] = 0;
                k--;
                moved = true;
            }

            if (k > 0 && cells[k - 1][j] == cells[k][j] && lastMerge != k - 1)
            {
                cells[k - 1][j] *= 2;
                cells[k][j] = 0;
                lastMerge = k - 1;
                moved = true;
            }
        }
    }
    return moved;
}

bool Grid::moveDown()
{
    bool moved = false;

    for (int j = 0; j < SIZE; j++)
    {
        int lastMerge = -1;
        for (int i = SIZE - 2; i >= 0; i--)
        {
            if (cells[i][j] == 0)
                continue;

            int k = i;
            while (k < SIZE - 1 && cells[k + 1][j] == 0)
            {
                cells[k + 1][j] = cells[k][j];
                cells[k][j] = 0;
                k++;
                moved = true;
            }

            if (k < SIZE - 1 && cells[k + 1][j] == cells[k][j] && lastMerge != k + 1)
            {
                cells[k + 1][j] *= 2;
                cells[k][j] = 0;
                lastMerge = k + 1;
                moved = true;
            }
        }
    }
    return moved;
}
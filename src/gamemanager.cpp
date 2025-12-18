#include "GameManager.h"
#include <cstdlib>
#include <ctime>

GameManager::GameManager(SDL_Renderer *r)
    : running(true), renderer(r)
{
    srand(time(nullptr));
}

void GameManager::run()
{
    while (running)
    {
        Direction dir = input.handleInput(running);
        bool moved = false;

        if (dir == Direction::LEFT)
            moved = grid.moveLeft();

        if (dir == Direction::RIGHT)
        {
            moved = grid.moveRight();
        }
        if (dir == Direction::UP)
        {
            moved = grid.moveUp();
        }
        if (dir == Direction::DOWN)
        {
            moved = grid.moveDown();
        }

        if (moved)
            grid.addRandomTile();

        renderer.draw(grid);
        SDL_Delay(16);
    }
}
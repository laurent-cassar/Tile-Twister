#include "RenderManager.h"

RenderManager::RenderManager(SDL_Renderer *r) : renderer(r) {}

void RenderManager::draw(const Grid &grid)
{
    SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < Grid::SIZE; i++)
    {
        for (int j = 0; j < Grid::SIZE; j++)
        {
            SDL_Rect rect = {j * 110 + 10, i * 110 + 10, 100, 100};
            if (grid.cells[i][j] == 0)
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            else
                SDL_SetRenderDrawColor(renderer, 255, 180, 100, 255);

            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}
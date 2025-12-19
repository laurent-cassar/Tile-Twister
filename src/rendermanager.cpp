#include "RenderManager.h"
#include <string>

RenderManager::RenderManager(SDL_Renderer *r) : renderer(r)
{
    font = TTF_OpenFont("asset/font/arial.ttf", 24);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
}

RenderManager::~RenderManager()
{
    TTF_CloseFont(font);
}

void RenderManager::draw(const Grid &grid)
{
    SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < Grid::SIZE; i++)
    {
        for (int j = 0; j < Grid::SIZE; j++)
        {
            int value = grid.cells[i][j];

            SDL_Rect tile = {j * 110 + 10, i * 110 + 10, 100, 100};
            SDL_Color color = getTileColor(value);

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
            SDL_RenderFillRect(renderer, &tile);

            if (value != 0 && font)
            {
                SDL_Color textColor = (value <= 4)
                                          ? SDL_Color{119, 110, 101, 255}
                                          : SDL_Color{249, 246, 242, 255};

                std::string text = std::to_string(value);

                SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), textColor);

                SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

                SDL_Rect dst;
                dst.w = surface->w;
                dst.h = surface->h;
                dst.x = tile.x + (tile.w - dst.w) / 2;
                dst.y = tile.y + (tile.h - dst.h) / 2;

                SDL_FreeSurface(surface);
                SDL_RenderCopy(renderer, texture, nullptr, &dst);
                SDL_DestroyTexture(texture);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

SDL_Color RenderManager::getTileColor(int value)
{
    switch (value)
    {
    case 2:
        return {238, 228, 218, 255};
    case 4:
        return {237, 224, 200, 255};
    case 8:
        return {242, 177, 121, 255};
    case 16:
        return {245, 149, 99, 255};
    case 32:
        return {246, 124, 95, 255};
    case 64:
        return {246, 94, 59, 255};
    case 128:
        return {237, 207, 114, 255};
    case 256:
        return {237, 204, 97, 255};
    case 512:
        return {237, 200, 80, 255};
    case 1024:
        return {237, 197, 63, 255};
    case 2048:
        return {237, 194, 46, 255};
    default:
        return {205, 193, 180, 255};
    }
}

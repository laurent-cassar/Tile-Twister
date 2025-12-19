#pragma once
#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Grid.h"

class RenderManager
{
public:
    RenderManager(SDL_Renderer *renderer);
    ~RenderManager();

    void draw(const Grid &grid);

private:
    SDL_Renderer *renderer;
    TTF_Font *font;

    SDL_Color getTileColor(int value);
};
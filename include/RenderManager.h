#pragma once
#include <SDL.h>
#include "Grid.h"

class RenderManager
{
public:
    RenderManager(SDL_Renderer *renderer);
    void draw(const Grid &grid);

private:
    SDL_Renderer *renderer;
};
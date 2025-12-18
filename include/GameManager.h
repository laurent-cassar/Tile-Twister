#pragma once
#include "Grid.h"
#include "InputManager.h"
#include "RenderManager.h"

class GameManager
{
public:
    GameManager(SDL_Renderer *renderer);
    void run();

private:
    bool running;
    Grid grid;
    InputManager input;
    RenderManager renderer;
};
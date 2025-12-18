#include "InputManager.h"

Direction InputManager::handleInput(bool &running)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            running = false;

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                return Direction::LEFT;
            case SDLK_RIGHT:
                return Direction::RIGHT;
            case SDLK_UP:
                return Direction::UP;
            case SDLK_DOWN:
                return Direction::DOWN;
            }
        }
    }
    return Direction::NONE;
}